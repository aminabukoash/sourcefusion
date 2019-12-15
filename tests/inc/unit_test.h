//
// Created by Chidiebere Onyedinma on 2019-12-15.
//

#ifndef SOURCEFUSION_UNIT_TEST_H
#define SOURCEFUSION_UNIT_TEST_H

#include "../../inc/sensor_fusion_common.hpp"
#include "../../inc/sensor_fusion_implementation.hpp"
#include "../../inc/fusion_algorithm.hpp"

#define ASSERT_RESULT(result) { if (result) { printf("#================================================#\n"); \
printf("TEST -> %s: PASSED!\n", __func__); printf("#================================================#\n"); } else \
{printf("#================================================#\n"); printf("TEST -> %s: FAILED!\n", __func__); \
printf("#================================================#\n");} }

void run_automated_unit_test();

void automated_degree_matrix_test();

void automated_eigenvalues_and_vectors_test();

void automated_principal_components_test();

void automated_contribution_rates_k_test();

void automated_contribution_rate_m_test();

void automated_integrated_support_scores_test();

void automated_eliminate_incorrect_data_test();

void automated_weight_coefficients_test();

void automated_fused_output_test();

void automated_perform_sensor_fusion_test();

#endif //SOURCEFUSION_UNIT_TEST_H
