/** @file unit_test.hpp
 * @brief Project unit tests declarations.
 *
 * Contains the function declarations for the project unit tests.
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

/**
 * @brief Check if two numbers are equal.
 *
 * Compare two numbers of type double and chechek if they're equal.
 * @param a The first number to be compared.
 * @param b The second number to be compared.
 * @return 0 if the numbers are equal, 1 otherwise.
 */
int compare_doubles(double a, double b);

/**
 * @test Unit test for the parse_file function.
 */
void automated_parse_input_file_test();

/**
 * @test Unit test for the compare_sensors_times function.
 */
void automated_compare_sensors_times_test();

/**
 * @test Unit test for the validate_interval function.
 */
void automated_validate_interval_test();

/**
 * @test Unit test for the create_sensor_from_line function.
 */
void automated_create_sensor_from_line_test();

/**
 * @test Unit test for the get_degree_matrix function.
 */
void automated_degree_matrix_test();

/**
 * @test Unit test for the get_eigenvalues_and_vectors function.
 */
void automated_eigenvalues_and_vectors_test();

/**
 * @test Unit test for the get_principal_components function.
 */
void automated_principal_components_test();

/**
 * @test Unit test for the get_contribution_rates function.
 */
void automated_contribution_rates_k_test();

/**
 * @test Unit test for the select_contribution_rate function.
 */
void automated_contribution_rate_m_test();

/**
 * @test Unit test for the get_integrated_support_scores function.
 */
void automated_integrated_support_scores_test();

/**
 * @test Unit test for the eliminate_incorrect_data function.
 */
void automated_eliminate_incorrect_data_test();

/**
 * @test Unit test for the get_weight_coefficients function.
 */
void automated_weight_coefficients_test();

/**
 * @test Unit test for the get_fused_output function.
 */
void automated_fused_output_test();

/**
 * @test Unit test for the perform_sensor_fusion function.
 */
void automated_perform_sensor_fusion_test();

#endif //SOURCEFUSION_UNIT_TEST_HPP
