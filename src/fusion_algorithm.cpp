
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


void vector_add(double* dest, double* src, int vector_size){
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

double *get_degree_matrix(SensorsList_t sensors_list) {
    int number_of_sensors = sensors_list.size();
    double *degree_matrix = (double *) malloc(number_of_sensors * number_of_sensors * sizeof(double));
    int index = 0;
    for (int i = 0; i < number_of_sensors; ++i) {
        for (int j = 0; j < number_of_sensors; ++j) {
            double degree = exp(-(abs(sensors_list[i].value - sensors_list[j].value)));
            degree_matrix[index] = degree;
            index++;
        }
    }
    return degree_matrix;
}

void
get_eigenvalues_and_vectors(double *degree_matrix, int number_of_sensors, double *eigenvalues, double **eigenvectors) {


    gsl_matrix_view m = gsl_matrix_view_array(degree_matrix, number_of_sensors, number_of_sensors);

    gsl_vector *eval = gsl_vector_alloc(number_of_sensors);
    gsl_matrix *evec = gsl_matrix_alloc(number_of_sensors, number_of_sensors);

    gsl_eigen_symmv_workspace *w = gsl_eigen_symmv_alloc(number_of_sensors);

    gsl_eigen_symmv(&m.matrix, eval, evec, w);

    gsl_eigen_symmv_free(w);

    gsl_eigen_symmv_sort(eval, evec, GSL_EIGEN_SORT_ABS_ASC);


    for (int i = 0; i < number_of_sensors; i++) {
        eigenvalues[i] = gsl_vector_get(eval, i);
        gsl_vector_view evec_i = gsl_matrix_column(evec, i);

        double * vec = (double*) malloc(number_of_sensors*sizeof(double));


        for (int j = 0; j < number_of_sensors; ++j) {
            vec[j] = evec_i.vector.data[j];
        }
        eigenvectors[i] = vec;
    }

    gsl_vector_free(eval);
    gsl_matrix_free(evec);
}


double* get_principal_components(double* eignvalues, double** eignvectors, int number_of_sensors){

    double * principal_components = (double*) malloc(number_of_sensors*sizeof(double));

    for (int i = 0; i < number_of_sensors; ++i) {
        principal_components[i] = vector_vector_multiply(eignvalues, eignvectors[i], number_of_sensors);
    }
    return principal_components;
}

double *get_contribution_rates(double *eignvalues,
                               int number_of_sensors) {
    double *contribution_rates = (double *) malloc(number_of_sensors
                                                   * sizeof(double));
    double eignvalue_sum = 0.0;
    for (int i = 0; i < number_of_sensors; ++i) {
        eignvalue_sum += eignvalues[i];
    }
    for (int i = 0; i < number_of_sensors; ++i) {
        contribution_rates[i] = eignvalues[i] / eignvalue_sum;
    }
    return contribution_rates;
}

double *get_cumulative_contributions(double *contribution_rates,
                                     int number_of_sensors) {
    double *cumulative_contributions = (double *) malloc(number_of_sensors
                                                         * sizeof(double));
    for (int i = 0; i < number_of_sensors; ++i) {
        cumulative_contributions[i] = 0.0;
        for (int j = 0; j <= i; ++j) {
            cumulative_contributions[i] += contribution_rates[j];
        }
    }
    return cumulative_contributions;
}

double *get_integrated_support_score(double **principal_components,
                                     double *contribution_rates,
                                     int number_of_sensors) {
    double *integrated_scores = (double *) malloc(number_of_sensors
                                                  * sizeof(double));
    for (int i = 0; i < number_of_sensors; ++i) {
        double *score = vector_scalar_multiply(principal_components[i],
                                               number_of_sensors,
                                               contribution_rates[i]);
        vector_add(integrated_scores, score, number_of_sensors);
    }
    return integrated_scores;
}

//double* get_weight_coefficients(double* integrated_scores){
//
//}
//
//double get_fused_output(double* sensor_values, double* weight_coefficients){
//
//}
