/** @file unit_test.hpp
 *  @brief contains the unit test headers
 *
 */

#ifndef SOURCEFUSION_UNIT_TEST_HPP
#define SOURCEFUSION_UNIT_TEST_HPP

#include "../../inc/sensor_fusion_common.hpp"
#include "../../inc/sensor_fusion_implementation.hpp"
#include "../../inc/fusion_algorithm.hpp"

#define ASSERT_RESULT(result, output) { if (result) { sprintf(output,"#=========================================\
=================#\n %s %s:"\
" %s#==========================================================#\n\n", "TEST -> ",__func__, "PASSED!\n");} else \
{sprintf(output, "#==========================================================#\n %s %s:"\
" %s#==========================================================#\n\n", "TEST -> ",__func__, "FAILED!\n");} }

void run_automated_unit_test();

int compare_doubles(double a,
                    double b);

void automated_parse_input_file_test();

void automated_compare_sensors_times_test();

void automated_validate_interval_test();

void automated_create_sensor_from_line_test();

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

#endif //SOURCEFUSION_UNIT_TEST_HPP
