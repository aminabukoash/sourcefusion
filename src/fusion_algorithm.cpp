
/** @file fusion_algorithm.cpp
 *  @brief contains the implementation of the sensor fusion algorithm
 */

// All C++ Headers
#include "../inc/sensor_fusion_common.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here

#ifdef __cplusplus
}
#endif

SensorsList_t remove_sensor_by_name(SensorsList_t sensors, char name[SENSOR_MAX_NAME_LEN]) {
    for (int i = 0; i < sensors.size(); ++i) {
        if (strcmp(sensors[i].name, name) == 0) {
            sensors.erase(sensors.begin() + i);
        }
    }
    return sensors;
}

void delete_element_from_double_array(double *array, int index, int size) {
    for (int i = index; i < size - 1; ++i) {
        array[i] = array[i + 1];
    }
}

double *get_degree_matrix(SensorsList_t sensors_list) {
    int number_of_sensors = sensors_list.size();
    double *degree_matrix = (double *) malloc(
            number_of_sensors * number_of_sensors * sizeof(double));

    printf("Degree Matrix:");

    int index = 0;
    for (int i = 0; i < number_of_sensors; ++i) {
        printf("\n");
        for (int j = 0; j < number_of_sensors; ++j) {
            double degree = exp(
                    -(fabs(sensors_list[i].value - sensors_list[j].value)));
            degree_matrix[index] = degree;
            printf("%f, ", degree);
            index++;
        }
    }
    printf("\n");
    return degree_matrix;
}

void get_eigenvalues_and_vectors(double *degree_matrix, int number_of_sensors,
                                 double *eigenvalues, double **eigenvectors) {

    double *degree_matrix_temp = (double *) calloc(number_of_sensors * number_of_sensors, sizeof(double));

    for (int k = 0; k < number_of_sensors * number_of_sensors; ++k) {
        degree_matrix_temp[k] = degree_matrix[k];
    }

    gsl_matrix_view m = gsl_matrix_view_array(degree_matrix_temp,
                                              number_of_sensors,
                                              number_of_sensors);

    gsl_vector *eval = gsl_vector_alloc(number_of_sensors);
    gsl_matrix *evec = gsl_matrix_alloc(number_of_sensors, number_of_sensors);

    gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc(number_of_sensors);

    gsl_eigen_symmv(&m.matrix, eval, evec, w);

    gsl_eigen_symmv_free(w);

    gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_VAL_DESC);


    for (int i = 0; i < number_of_sensors; i++) {
        eigenvalues[i] = gsl_vector_get(eval, i);
        gsl_vector_view evec_i = gsl_matrix_column(evec, i);

        double *vec = (double *) calloc(number_of_sensors, sizeof(double));
        printf("Eigenvalues : %f - ", eigenvalues[i]);
        printf("Eigenvector : [");
        for (int j = 0; j < number_of_sensors; ++j) {
            vec[j] = evec_i.vector.data[j];
            printf("%f, ", vec[j]);
        }
        printf("]\n");
        eigenvectors[i] = vec;
    }

    free(degree_matrix_temp);
    gsl_vector_free(eval);
    gsl_matrix_free(evec);
}


double **get_principal_components(double *degree_matrix, double **eignvectors, int number_of_sensors) {

    double **principal_components = (double **) calloc(number_of_sensors, sizeof(double *));
    for (int i = 0; i < number_of_sensors; i++) {
        principal_components[i] = (double *) calloc(number_of_sensors, sizeof(double));
    }

    gsl_matrix *p_eigen_vec = gsl_matrix_alloc(number_of_sensors, number_of_sensors);
    gsl_matrix *p_support_degree = gsl_matrix_alloc(number_of_sensors, number_of_sensors);
    gsl_matrix *p_y = gsl_matrix_alloc(number_of_sensors, number_of_sensors);

    for (int i = 0; i < number_of_sensors; i++) {
        for (int j = 0; j < number_of_sensors; j++) {
            gsl_matrix_set(p_eigen_vec, i, j, eignvectors[i][j]);
            gsl_matrix_set(p_support_degree, i, j,
                           degree_matrix[j + (i * number_of_sensors)]);
            gsl_matrix_set(p_y, i, j, 0.0);
        }
    }


    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,
                   1.0, p_eigen_vec, p_support_degree,
                   0.0, p_y);

    printf("\n\nPrincipal components : \n");
    for (int rows = 0; rows < number_of_sensors; rows++) {

        for (int cols = 0; cols < number_of_sensors; cols++) {
            principal_components[rows][cols] = gsl_matrix_get(p_y, rows, cols);
            printf("%f, ", principal_components[rows][cols]);
        }
    }
    printf("\n");
    return principal_components;
}

double *get_contribution_rates(double *eigenvalues, int number_of_sensors) {
    double *contribution_rates = (double *) calloc(number_of_sensors, sizeof(double));
    double eignvalue_sum = 0.0;
    for (int i = 0; i < number_of_sensors; ++i) {
        double val = eigenvalues[i];
        eignvalue_sum += eigenvalues[i];
    }
    printf("\n\nContribution rates: :\n");

    for (int i = 0; i < number_of_sensors; ++i) {
        contribution_rates[i] = eigenvalues[i] / eignvalue_sum;
        printf("%f, ", contribution_rates[i]);
    }
    printf("\n");
    return contribution_rates;
}


int select_contribution_rate(double *contribution_rates, int number_of_sensors,
                             float p) {
    double *cumulative_contributions = (double *) malloc(number_of_sensors * sizeof(double));

    for (int i = 0; i < number_of_sensors; ++i) {
        cumulative_contributions[i] = 0.0;
        for (int j = 0; j <= i; ++j) {
            cumulative_contributions[i] += contribution_rates[j];
        }
    }
    printf("\n\nStep 5: \n");
    for (int k = 0; k < number_of_sensors; ++k) {
        if (cumulative_contributions[k] > p) {
            int m = k + 1;
            printf("The value of m is: %d\n", m);
            return m;
        }
    }

}

double *get_integrated_support_scores(double **principal_components,
                              double *contribution_rates, int number_of_sensors, int m) {
    double *integrated_scores = (double *) calloc(number_of_sensors, sizeof(double));

    for (int i = 0; i < number_of_sensors; i++) {
        for (int j = 0; j < m; j++) {
            integrated_scores[i] += (contribution_rates[j] *principal_components[j][i]);
        }
    }
    printf("Step 6\n Integrated scores: [");

    for (int j = 0; j < number_of_sensors; ++j) {
        printf("%f, ", integrated_scores[j]);
    }
    printf("]\n");
    return integrated_scores;
}


SensorsList_t eliminate_incorrect_data(SensorsList_t sensors_list, double *integrated_scores, float tolerance) {
    double threshold_value;
    double scores_sum = 0.0;
    int number_of_sensors = sensors_list.size();
    char sensors_to_be_deleted_names[number_of_sensors][SENSOR_MAX_NAME_LEN];
    int sensors_to_be_deleted_indices[number_of_sensors];
    int deleted_count = 0;

    threshold_value = fabs((scores_sum / number_of_sensors) * tolerance);

    for (int j = 0; j < number_of_sensors; ++j) {
        if (fabs(integrated_scores[j]) < threshold_value) {
            sensors_to_be_deleted_indices[deleted_count] = j;
            strncpy(sensors_to_be_deleted_names[deleted_count],
                    sensors_list[j].name, SENSOR_MAX_NAME_LEN);
            deleted_count++;
        }
    }

    for (int k = 0; k < deleted_count; ++k) {
        delete_element_from_double_array(integrated_scores,sensors_to_be_deleted_indices[k] - k,
                                         number_of_sensors);
        sensors_list = remove_sensor_by_name(sensors_list, sensors_to_be_deleted_names[k]);
        number_of_sensors--;
    }

    return sensors_list;
}

double *get_weight_coefficients(double *integrated_scores, int number_of_sensors) {

    double scores_sum = 0.0;
    double *weight_coefficients = (double *) malloc(number_of_sensors * sizeof(double));

    for (int i = 0; i < number_of_sensors; ++i) {
        scores_sum += integrated_scores[i];
    }

    for (int i = 0; i < number_of_sensors; ++i) {
        weight_coefficients[i] = integrated_scores[i] / scores_sum;
    }

    return weight_coefficients;
}

double
get_fused_output(SensorsList_t sensors_list, double *weight_coefficients) {
    double fused_output = 0.0;
    int number_of_sensors = sensors_list.size();

    for (int i = 0; i < number_of_sensors; ++i) {
        fused_output += sensors_list[i].value * weight_coefficients[i];
    }

    return fused_output;
}

double perform_sensor_fusion(SensorsList_t sensors, float p, float tolerance) {

    int number_of_sensors = sensors.size();

    double *degree_matrix = get_degree_matrix(sensors);

    double **eigenvectors = (double **) malloc(number_of_sensors * sizeof(double *));
    double *eigenvalues = (double *) malloc(number_of_sensors * sizeof(double));
    get_eigenvalues_and_vectors(degree_matrix, number_of_sensors, eigenvalues, eigenvectors);

    double **principal_components = get_principal_components(degree_matrix, eigenvectors, number_of_sensors);

    double *contribution_rates = get_contribution_rates(eigenvalues,
                                                        number_of_sensors);

    int m = select_contribution_rate(contribution_rates, number_of_sensors, p);

    double *integrated_support_scores = get_integrated_support_scores(
            principal_components, contribution_rates, number_of_sensors, m);

    eliminate_incorrect_data(sensors, integrated_support_scores, tolerance);

    double *weight_coefficients = get_weight_coefficients(integrated_support_scores,
            sensors.size());

    return get_fused_output(sensors, weight_coefficients);

}
