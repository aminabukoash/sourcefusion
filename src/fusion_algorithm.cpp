
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

void vector_add(double *dest, double *src, int vector_size) {
    for (int i = 0; i < vector_size; ++i) {
        dest[i] += src[i];
    }
}

double *vector_scalar_multiply(double *vector, int vector_size, double scalar) {
    for (int i = 0; i < vector_size; ++i) {
        vector[i] *= scalar;
    }
    return vector;
}

double vector_vector_multiply(double *vector1, double *vector2, int vector_size) {
    double product = 0;
    for (int i = 0; i < vector_size; ++i) {
        product += (vector1[i] * vector2[i]);
    }
    return product;
}

SensorsList_t remove_sensor_by_name(SensorsList_t sensors, char name[SENSOR_MAX_NAME_LEN]) {
    for (int i = 0; i < sensors.size(); ++i) {
        if (strcmp(sensors[i].name, name) == 0) {
            sensors.erase(sensors.begin() + i);
        }
    }
    return sensors;
}

void delete_element_from_double_array(double* array, int index, int size){
    for (int i = index; i < size-1; ++i) {
        array[i] = array[i+1];
    }
}

double **get_degree_matrix(SensorsList_t sensors_list) {
    int number_of_sensors = sensors_list.size();
    double **degree_matrix = (double **) malloc(number_of_sensors * number_of_sensors * sizeof(double*));
    for(int i=0;i<number_of_sensors;i++){
        degree_matrix[i]=(double *)malloc(number_of_sensors * sizeof(double));
    }
    for (int i = 0; i < number_of_sensors; ++i) {
        for (int j = 0; j < number_of_sensors; ++j) {
            double degree = exp(-fabs(sensors_list[i].value - sensors_list[j].value));
            degree_matrix[i][j] = degree;
        }
    }
    return degree_matrix;
}

void get_eigenvalues_and_vectors(double **degree_matrix, int number_of_sensors,
        double *eigenvalues, double **eigenvectors) {


    gsl_matrix *p_m =gsl_matrix_alloc(number_of_sensors,number_of_sensors);

    for (int k = 0; k < number_of_sensors; ++k) {
        for (int i = 0; i < number_of_sensors; ++i) {
            gsl_matrix_set(p_m, k, i, degree_matrix[k][i]);
        }
    }

    gsl_vector *eval = gsl_vector_alloc(number_of_sensors);
    gsl_matrix *evec = gsl_matrix_alloc(number_of_sensors, number_of_sensors);

    gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc(number_of_sensors);

    gsl_eigen_symmv(p_m, eval, evec, w);

    gsl_eigen_symmv_free(w);

    gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_VAL_DESC);


    for (int i = 0; i < number_of_sensors; i++) {
        eigenvalues[i] = gsl_vector_get(eval, i);
        gsl_vector_view evec_i = gsl_matrix_column(evec, i);

        double *vec = (double *) malloc(number_of_sensors * sizeof(double));


        for (int j = 0; j < number_of_sensors; ++j) {
            vec[j] = evec_i.vector.data[j];
        }
        eigenvectors[i] = vec;
    }

    gsl_vector_free(eval);
    gsl_matrix_free(evec);
}


double **get_principal_components(double **degree_matrix, double **eignvectors, int number_of_sensors) {

    double **principal_components = (double **) malloc(number_of_sensors * sizeof(double*));
    for(int i=0;i<number_of_sensors;i++){
        principal_components[i]=(double *)malloc(number_of_sensors * sizeof(double));
    }


    gsl_matrix *p_eigen_vec=gsl_matrix_alloc(number_of_sensors,number_of_sensors);
    gsl_matrix *p_support_degree=gsl_matrix_alloc(number_of_sensors,number_of_sensors);
    gsl_matrix *p_y=gsl_matrix_alloc(number_of_sensors,number_of_sensors);


    for(int i=0;i<number_of_sensors;i++){
        for(int j=0;j<number_of_sensors;j++)
        {
            gsl_matrix_set(p_eigen_vec,i,j,eignvectors[i][j]);
            gsl_matrix_set(p_support_degree,i,j,degree_matrix[i][j]);
            gsl_matrix_set(p_y,i,j,0.0);
        }
    }


    gsl_blas_dgemm (CblasNoTrans, CblasNoTrans,
                    1.0, p_eigen_vec,p_support_degree,
                    0.0, p_y);


    for(int rows=0;rows<number_of_sensors;rows++){
        for(int cols=0;cols<number_of_sensors;cols++)
        {
            principal_components[rows][cols]=gsl_matrix_get(p_y,rows,cols);
        }
    }
    return principal_components;
}

double *get_contribution_rates(double *eigenvalues, int number_of_sensors) {
    double *contribution_rates = (double *) malloc(number_of_sensors * sizeof(double));
    double eignvalue_sum = 0.0;
    for (int i = 0; i < number_of_sensors; ++i) {
        eignvalue_sum += eigenvalues[i];
    }
    for (int i = 0; i < number_of_sensors; ++i) {
        contribution_rates[i] = eigenvalues[i] / eignvalue_sum;
    }
    return contribution_rates;
}



int select_contribution_rate(double *contribution_rates, int number_of_sensors, float p) {
    double *cumulative_contributions = (double *) malloc(number_of_sensors * sizeof(double));

    for (int i = 0; i < number_of_sensors; ++i) {
        double sum = 0.0;
        for (int j = 0; j <= i; ++j) {
            sum += contribution_rates[j];
        }
        cumulative_contributions[i] = sum;
    }

    int m;

    for (int k = 0; k < number_of_sensors; ++k) {
        if (cumulative_contributions[k] > p) {
            m = k + 1;
            break;
        }
    }
    free(cumulative_contributions);
    return m;

}

double *get_integrated_support_scores(double** principal_components, double *contribution_rates, int number_of_sensors, int m) {
    double *integrated_scores = (double *) malloc(number_of_sensors* sizeof(double));

    for (int i = 0; i < number_of_sensors; ++i) {

        integrated_scores[i] = 0;

        for (int j = 0; j < m; ++j) {
            integrated_scores[i] = integrated_scores[i] + (contribution_rates[j] * principal_components[j][i]);
        }

    }

    return integrated_scores;
}


SensorsList_t eliminate_incorrect_data(SensorsList_t sensors_list, double *integrated_scores, float tolerance) {
    double sum = 0.0;
    int number_of_sensors = sensors_list.size();

    int* index_to_be_deleted = (int*)calloc(number_of_sensors,sizeof(int));

    for (int i = 0; i < number_of_sensors; ++i) {
        sum+=integrated_scores[i];
    }

    double value_to_compare = fabs(sum/number_of_sensors) * tolerance;

    for (int j = 0; j < number_of_sensors; ++j) {
        if (fabs(integrated_scores[j]) < value_to_compare){
            index_to_be_deleted[j] = 1;
        }
    }

    SensorsList_t reduced_list;


    for (int k = 0; k < number_of_sensors; ++k) {
        if (index_to_be_deleted[k] == 0){
            reduced_list.push_back(sensors_list.at(k));
        }
    }

    return reduced_list;
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

double get_fused_output(SensorsList_t sensors_list, double *weight_coefficients) {
    double fused_output = 0.0;
    int number_of_sensors = sensors_list.size();

    for (int i = 0; i < number_of_sensors; ++i) {
        fused_output += sensors_list[i].value * weight_coefficients[i];
    }

    return fused_output;
}

double perform_sensor_fusion(SensorsList_t sensors, float p, float tolerance) {

    int number_of_sensors = sensors.size();

    double **degree_matrix = get_degree_matrix(sensors);

    double **eigenvectors = (double **) malloc(number_of_sensors * sizeof(double *));
    double *eigenvalues = (double *) malloc(number_of_sensors * sizeof(double));

    get_eigenvalues_and_vectors(degree_matrix, number_of_sensors, eigenvalues, eigenvectors);

    double **principal_components = get_principal_components(degree_matrix, eigenvectors, number_of_sensors);

    double *contribution_rates = get_contribution_rates(eigenvalues, number_of_sensors);

    int m = select_contribution_rate(contribution_rates, number_of_sensors, p);

    double* integrated_support_scores = get_integrated_support_scores(principal_components, contribution_rates, number_of_sensors, m);

    SensorsList_t reduced_list = eliminate_incorrect_data(sensors,integrated_support_scores, tolerance);

    printf("new list size: %lu\n", reduced_list.size());

    double* weight_coefficients = get_weight_coefficients(integrated_support_scores, reduced_list.size());

    double fused_output = get_fused_output(reduced_list, weight_coefficients);

    free(degree_matrix);
    free(eigenvectors);
    free(eigenvalues);
    free(principal_components);
    free(contribution_rates);
    free(integrated_support_scores);
    free(weight_coefficients);

    return fused_output;

}
