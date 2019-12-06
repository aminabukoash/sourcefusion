/** @file fusion_algorithm.hpp
 * Contains the declarations for the fusion algorithm functions.
 */

#ifndef FUSION_ALGORITHM_HPP_
#define FUSION_ALGORITHM_HPP_

// All C++ Headers
#include "../inc/sf_common.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here

#ifdef __cplusplus
}
#endif

/**
 *  Calculate the support degree matrix.
 * @param values Sensor values at a specific timestamp.
 * @return
 */
float** get_degree_matrix(float* values);

/**
 * Calculate all the eigenvalues for the support degree matrix.
 * @param degree_matrix The support degree matrix of sensor inputs at a certain timestamp.
 * @return The eigenvalues for the support degree matrix.
 */
float* get_eignvalues(float** degree_matrix);

/**
 * Calculate all the eigenvectors for the support degree matrix.
 * @param degree_matrix The support degree matrix of sensor inputs at a certain timestamp.
 * @return The eigenvectors for the support degree matrix.
 */
float** get_eignvectors(float** degree_matrix);

/**
 *  Calculate the principal components of the support degree matrix.
 * @param eignvalues The eigenvalues for the support degree matrix.
 * @param eignvectors The eigenvectors for the support degree matrix.
 * @return The principal components of the support degree matrix.
 */
float* get_principal_components(float* eignvalues, float** eignvectors);

/**
 *  Calculate the contribution rates of the individual principal components.
 * @param principal_components The principal components of the support degree matrix.
 * @return The individual contribution rates of the principal components.
 */
float* get_contribution_rates(float* principal_components, int number_of_sensors);

/**
 *  Calculate the cumulative contribution rates up to the m principal component.
 * @param contribution_rates The individual contribution rates of the principal components.
 * @return The cumulative contribution rates up to the m principal component.
 */
float* get_cumulative_contributions(float* contribution_rates, int number_of_sensors);

/**
 * Compute the integrated support degree score for all sensors.
 * @param principal_components The principal components of the support degree matrix.
 * @param contribution_rates The individual contribution rates of the principal components.
 * @return The integrated support degree score for all sensors.
 */
float* get_integrated_support_score(float** principal_components, float* contribution_rates, int number_of_sensors);

/**
 *  Compute the weight coefficient for each sensor.
 * @param integrated_scores The integrated support degree score for all sensors.
 * @return The weight coefficient for each sensor.
 */
float* get_weight_coefficients(float* integrated_scores);

/**
 *  Compute the fused output for all sensors.
 * @param sensor_values The sensor values.
 * @param weight_coefficients the weight coefficient for each sensor
 * @return The fused output for all sensors.
 */
float get_fused_output(float* sensor_values, float* weight_coefficients);


#endif /* FUSION_ALGORITHM_HPP_ */
