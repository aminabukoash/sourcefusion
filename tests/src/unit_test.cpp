//
// Created by Chidiebere Onyedinma on 2019-12-15.
//

#include "../inc/unit_test.h"

void run_automated_unit_test() {

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

void automated_degree_matrix_test() {

    double expected_result[4][4] = {{1.000000, 0.548812, 0.606531, 1.000000},
                                    {0.548812, 1.000000, 0.904837, 0.548812},
                                    {0.606531, 0.904837, 1.000000, 0.606531},
                                    {1.000000, 0.548812, 0.606531, 1.000000}};


    Sensor_t sensor = {.value=53.2, .time=make_time("12:00"), .name = "sens1"};
    Sensor_t sensor2 = {.value=52.6, .time=make_time("12:00"), .name = "sens2"};
    Sensor_t sensor3 = {.value=52.7, .time=make_time("12:00"), .name = "sens3"};
    Sensor_t sensor4 = {.value=53.2, .time=make_time("12:00"), .name = "sens4"};

    SensorsList_t list;

    list.push_back(sensor);
    list.push_back(sensor2);
    list.push_back(sensor3);
    list.push_back(sensor4);

    double **degree_matrix = get_degree_matrix(list);

    int result = 1;
    double precision = 0.000001;

    for (int i = 0; i < list.size(); ++i) {
        for (int j = 0; j < list.size(); ++j) {

            if (!(((expected_result[i][j] - precision) < degree_matrix[i][j]) &&
                  ((expected_result[i][j] + precision) > degree_matrix[i][j]))) {
                result = 0;
            }
        }
    }

    ASSERT_RESULT(result)


}

void automated_eigenvalues_and_vectors_test() {

}

void automated_principal_components_test() {

}

void automated_contribution_rates_k_test() {

}

void automated_contribution_rate_m_test() {

}

void automated_integrated_support_scores_test() {

}

void automated_eliminate_incorrect_data_test() {

}

void automated_weight_coefficients_test() {

}

void automated_fused_output_test() {

}

void automated_perform_sensor_fusion_test() {

}

int _main() {
    run_automated_unit_test();
    return 0;
}