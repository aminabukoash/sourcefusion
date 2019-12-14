
/** @file fusion_algorithm.hpp
 * Contains the declarations for the fusion algorithm functions.
 */

#ifndef FUSION_ALGORITHM_HPP_
#define FUSION_ALGORITHM_HPP_

// All C++ Headers
#include "sensor_fusion_common.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here

#ifdef __cplusplus
}
#endif

/**
*  Helper function - Adds the second double vector to the first one.
* @param dest The vector that will be added to.
* @param src The vector that will be used to add.
* @param vector_size the size of the vectors.
*/
void vector_add(double* dest, double* src, int vector_size);

/**
 *  Helper function - Multiplies a vector by a double scalar value.
 * @param vector The vector that will be multiplied.
 * @param vector_size the size of the vectors.
 * @param scalar the scalar that will be used to multiply of the vectors.
 */
double *vector_scalar_multiply(double *vector, int vector_size, double scalar);

/**
 *  Helper function - Multiplies a vector by another vector.
 * @param vector1 The first vector that will be multiplied.
 * @param vector2 The second vector that will be multiplied.
 * @param vector_size the size of the vectors.
 * @return the sum of the multiplied vectors.
 */
double vector_vector_multiply(double *vector1, double *vector2, int vector_size);

/**
 *  Helper function - Removes a sensor from the list by it's name..
 * @param sensors The sensors list vector.
 * @param name The name of the sensor to be removed.
 * @return the modified sesnsor list.
 */
SensorsList_t remove_sensor_by_name(SensorsList_t sensors, char* name);

/**
 *  Calculate the support degree matrix.
 * @param values Sensor values at a specific timestamp.
 * @return
 */
double* get_degree_matrix(SensorsList_t sensors_list);

/**
 * Calculate all the eigenvalues and vectors for the support degree matrix.
 * @param degree_matrix The support degree matrix of sensor inputs at a certain timestamp.
 * @param eigenvalues The eigenvalues for the support degree matrix.
 * @param eigenvectors The eigenvectors for the support degree matrix.
 */
void get_eigenvalues_and_vectors(double* degree_matrix, int number_of_sensors, double* eigenvalues, double** eigenvectors);


/**
 *  Calculate the principal components of the support degree matrix.
 * @param eignvalues The eigenvalues for the support degree matrix.
 * @param eignvectors The eigenvectors for the support degree matrix.
 * @return The principal components of the support degree matrix.
 */
double* get_principal_components(double* eignvalues, double** eignvectors);

/**
 *  Calculate the contribution rates of the individual principal components.
 * @param principal_components The principal components of the support degree matrix.
 * @param number_of_sensors The total sensor count.
 * @return The individual contribution rates of the principal components.
 */
double* get_contribution_rates(double* principal_components, int number_of_sensors);

/**
 *  Calculate the cumulative contribution rates up to the m principal component.
 * @param contribution_rates The individual contribution rates of the principal components.
 * @param number_of_sensors The total sensor count.
 * @param p The contribution parameter p.
 * @return The cumulative contribution rates up to the m principal component.
 */
double* get_cumulative_contributions(double* contribution_rates, int number_of_sensors, float p);

/**
 * Compute the integrated support degree score for all sensors.
 * @param principal_components The principal components of the support degree matrix.
 * @param contribution_rates The individual contribution rates of the principal components.
 * @param number_of_sensors The total sensor count.
 * @return The integrated support degree score for all sensors.
 */
double* get_integrated_support_score(double** principal_components, double* contribution_rates, int number_of_sensors);

/**
 *  Remove sensors from the list that are not supported by q% of the sensors.
 * @param sensors The sensors list vector.
 * @param integrated_scores  The integrated support degree score for all sensors.
 * @param tolerance The fault tolerance value..
 * @return the modified sensor list without faulty sensors.
 */
SensorsList_t eliminate_incorrect_data(SensorsList_t sensors_list, double *integrated_scores, float tolerance);

/**
 *  Compute the weight coefficient for each sensor.
 * @param integrated_scores The integrated support degree score for all sensors.
 * @return The weight coefficient for each sensor.
 */
double* get_weight_coefficients(double* integrated_scores, int number_of_sensors);

/**
 *  Compute the fused output for all sensors.
 * @param sensor_values The sensor values.
 * @param weight_coefficients the weight coefficient for each sensor
 * @return The fused output for all sensors.
 */
double get_fused_output(SensorsList_t sensors_list, double* weight_coefficients);


#endif /* FUSION_ALGORITHM_HPP_ */
