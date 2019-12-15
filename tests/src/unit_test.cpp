//
// Created by Chidiebere Onyedinma on 2019-12-15.
//

#include "../inc/unit_test.h"

#define NO_OF_SENSOR_TEST 4
#define PRECISION 0.000001
#define ALGORITHM_PARAMETER 0.85
#define TOLERANCE 0.70
#define M 2

double DEGREE_MATRIX_DATA[16] = {1.000000, 0.548812, 0.606531, 1.000000,
                                 0.548812, 1.000000, 0.904837, 0.548812,
                                 0.606531, 0.904837, 1.000000, 0.606531,
                                 1.000000, 0.548812, 0.606531, 1.000000};

double EIGENVALUES[4] = {3.109316, 0.798365, 0.092319, 0.000000};

double EIGENVECTORS[4][4] = {{0.510252,  -0.488296, -0.034787, 0.707107},
                             {-0.488296, -0.034787, 0.707107,  0.479665},
                             {-0.034787, 0.707107,  0.479665,  0.549943},
                             {0.707107,  0.479665,  0.549943,  -0.683728}};

double PRINCIPAL_COMPONENTS[4][4] = {{0.928277, 0.148329, 0.261751, 0.928277},
                                     {0.401160, 0.600293, 0.670395, 0.401160},
                                     {1.194156, 1.423849, 1.431940, 1.194156},
                                     {0.620182, 0.990104, 0.998142, 0.620182}};

double CONTRIBUTION_RATES[4] = {0.777329, 0.199591, 0.023080, 0.000000};

double INTEGRATED_SUPPORT_SCORE[4] = {0.801645, 0.235114, 0.337271, 0.801645};

double WEIGHT_COEFFICIENTS[2] = {0.773222,0.226778};

SensorsList_t list, reduced_list;


void run_automated_unit_test() {

    Sensor_t sensor = {.value=53.2, .time=make_time("12:00"), .name = "sens1"};
    Sensor_t sensor2 = {.value=52.6, .time=make_time("12:00"), .name = "sens2"};
    Sensor_t sensor3 = {.value=52.7, .time=make_time("12:00"), .name = "sens3"};
    Sensor_t sensor4 = {.value=53.2, .time=make_time("12:00"), .name = "sens4"};

    list.push_back(sensor);
    list.push_back(sensor2);
    list.push_back(sensor3);
    list.push_back(sensor4);

    automated_degree_matrix_test();
    automated_eigenvalues_and_vectors_test();
    automated_principal_components_test();
    automated_contribution_rates_k_test();
    automated_contribution_rate_m_test();
    automated_integrated_support_scores_test();
    automated_eliminate_incorrect_data_test();
    automated_weight_coefficients_test();
    automated_fused_output_test();
    automated_perform_sensor_fusion_test();

}

int compare_doubles(double a, double b) {
    if (((a - PRECISION) < b) &&
        ((a + PRECISION) > b)) {
        return 1;
    } else {
        return 0;
    }
}

void automated_degree_matrix_test() {

    double *degree_matrix = get_degree_matrix(list);

    int result = 1;

    for (int i = 0; i < NO_OF_SENSOR_TEST; ++i) {

        result = compare_doubles(DEGREE_MATRIX_DATA[i], degree_matrix[i]);
        if(result == 0){
            break;
        }

    }

    ASSERT_RESULT(result)


}

void automated_eigenvalues_and_vectors_test() {
    int result = 1;

    double **eigenvectors = (double **) malloc(NO_OF_SENSOR_TEST * sizeof(double *));
    double *eigenvalues = (double *) malloc(NO_OF_SENSOR_TEST * sizeof(double));
    get_eigenvalues_and_vectors(DEGREE_MATRIX_DATA, NO_OF_SENSOR_TEST, eigenvalues, eigenvectors);

    for (int i = 0; i < NO_OF_SENSOR_TEST; ++i) {
        result = compare_doubles(EIGENVALUES[i], eigenvalues[i]);
        if(result == 0){
            break;
        }
        for (int j = 0; j < NO_OF_SENSOR_TEST; ++j) {
            result = compare_doubles(EIGENVECTORS[i][j], eigenvectors[i][j]);
            if(result == 0){
                break;
            }
        }

    }
    ASSERT_RESULT(result)
}

void automated_principal_components_test() {
    int result = 1;

    double** eigenvectors = (double**)malloc(NO_OF_SENSOR_TEST * sizeof(double*));
    for (int i = 0; i < NO_OF_SENSOR_TEST; ++i) {
        eigenvectors[i] = (double*)malloc(NO_OF_SENSOR_TEST * sizeof(double));
        eigenvectors[i] = EIGENVECTORS[i];
    }

    double **principal_components = get_principal_components(DEGREE_MATRIX_DATA, eigenvectors, NO_OF_SENSOR_TEST);

    for (int j = 0; j < NO_OF_SENSOR_TEST; ++j) {
        for (int i = 0; i < NO_OF_SENSOR_TEST; ++i) {
            result = compare_doubles(PRINCIPAL_COMPONENTS[j][i], principal_components[j][i]);
            if(result == 0){
                break;
            }
        }
        if(result == 0){
            break;
        }
    }

    ASSERT_RESULT(result)

}

void automated_contribution_rates_k_test() {
    int result = 1;

    double *contribution_rates = get_contribution_rates(EIGENVALUES, NO_OF_SENSOR_TEST);

    for (int i = 0; i < NO_OF_SENSOR_TEST; ++i) {
        result = compare_doubles(CONTRIBUTION_RATES[i], contribution_rates[i]);
        if(result == 0){
            break;
        }
    }

    ASSERT_RESULT(result)
}

void automated_contribution_rate_m_test() {
    int result = 1;
    int m = select_contribution_rate(CONTRIBUTION_RATES, NO_OF_SENSOR_TEST, ALGORITHM_PARAMETER);
    if(M != m){
        result = 0;
    }
    ASSERT_RESULT(result)
}

void automated_integrated_support_scores_test() {

    int result = 1;

    double **principal_components = (double**)malloc(NO_OF_SENSOR_TEST * sizeof(double*));
    for (int i = 0; i < NO_OF_SENSOR_TEST; ++i) {
        principal_components[i] = (double*)malloc(NO_OF_SENSOR_TEST * sizeof(double));
        principal_components[i] = PRINCIPAL_COMPONENTS[i];
    }

    double *integrated_support_scores = get_integrated_support_scores(
            principal_components, CONTRIBUTION_RATES, NO_OF_SENSOR_TEST, M);

    for (int j = 0; j < NO_OF_SENSOR_TEST; ++j) {
        result = compare_doubles(INTEGRATED_SUPPORT_SCORE[j], integrated_support_scores[j]);
        if(result == 0){
            break;
        }
    }

    ASSERT_RESULT(result)

    free(principal_components);
}

void automated_eliminate_incorrect_data_test() {
    int result = 1;

  reduced_list =  eliminate_incorrect_data(list, INTEGRATED_SUPPORT_SCORE,TOLERANCE);
  if(reduced_list.size() != 2){
      result = 0;
  }

  ASSERT_RESULT(result)
}

void automated_weight_coefficients_test() {
    int result = 1;
    double *weight_coefficients = get_weight_coefficients(INTEGRATED_SUPPORT_SCORE,
                                                          reduced_list.size());

    for (int i = 0; i < reduced_list.size(); ++i) {
        result = compare_doubles(WEIGHT_COEFFICIENTS[i], weight_coefficients[i]);
        if(result == 0){
            break;
        }
    }

    ASSERT_RESULT(result)

}

void automated_fused_output_test() {
    double fused_output = get_fused_output(reduced_list, WEIGHT_COEFFICIENTS);
    int result = compare_doubles(53.200000, fused_output);
    ASSERT_RESULT(result)
}

void automated_perform_sensor_fusion_test() {
    double fuse_final = perform_sensor_fusion(list, ALGORITHM_PARAMETER, TOLERANCE);
    int result = compare_doubles(53.200000, fuse_final);
    ASSERT_RESULT(result)
}

int _main() {
    run_automated_unit_test();
    return 0;
}