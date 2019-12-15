
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
 *  Helper function - Removes a sensor from the list by it's name..
 * @param sensors The sensors list vector.
 * @param name The name of the sensor to be removed.
 * @return the modified sesnsor list.
 */
SensorsList_t remove_sensor_by_name(SensorsList_t sensors, char* name);

/**
 *  Helper function - Deletes element from a double array.
 * @param array The array to be deleted from.
 * @param index The index to start deleting
 * @param size number of elements to be deleted
 */
void delete_element_from_double_array(double* array, int index, int size);

/**
 *  Calculate the support degree matrix.
 * @param values Sensor values at a specific timestamp.
 * @return
 */
double** get_degree_matrix(SensorsList_t sensors_list);

/**
 * Calculate all the eigenvalues and vectors for the support degree matrix.
 * @param degree_matrix The support degree matrix of sensor inputs at a certain timestamp.
 * @param eigenvalues The eigenvalues for the support degree matrix.
 * @param eigenvectors The eigenvectors for the support degree matrix.
 */
void get_eigenvalues_and_vectors(double** degree_matrix, int number_of_sensors, double* eigenvalues, double** eigenvectors);


/**
 *  Calculate the principal components of the support degree matrix.
 * @param eigenvalues The eigenvalues for the support degree matrix.
 * @param eigenvectors The eigenvectors for the support degree matrix.
 * @param number_of_sensors The total sensor count.
 * @return The principal components of the support degree matrix.
 */
double **get_principal_components(double **degree_matrix, double **eignvectors, int number_of_sensors);

/**
 *  Calculate the contribution rates of the individual principal components.
 * @param eigenvalues The eigenvalues for the support degree matrix.
 * @param number_of_sensors The total sensor count.
 * @return The individual contribution rates of the principal components.
 */
double* get_contribution_rates(double* eigenvalues, int number_of_sensors);

/**
 *  Select the contribution rate that satisfies P.
 *  @param rates_to_be_deleted_indices the indices of rates to be deleted
 * @param contribution_rates The individual contribution rates of the principal components.
 * @param number_of_sensors The total sensor count.
 * @param p The contribution parameter p.
 */
int select_contribution_rate(double *contribution_rates,
                             int number_of_sensors, float p);

/**
 * Compute the integrated support degree score for all sensors.
 * @param principal_components The principal components of the support degree matrix.
 * @param contribution_rates The individual contribution rates of the principal components.
 * @param number_of_sensors The total sensor count.
 * @return The integrated support degree score for all sensors.
 */
double *get_integrated_support_scores(double** principal_components, double *contribution_rates, int number_of_sensors, int m);

/**
 *  Remove sensors from the list that are not supported by q% of the sensors.
 * @param sensors The sensors list vector.
 * @param integrated_scores  The integrated support degree score for all sensors.
 * @param tolerance The fault tolerance value.
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
 * @param weight_coefficients the weight coefficient for each sensor.
 * @return The fused output for all sensors.
 */
double get_fused_output(SensorsList_t sensors_list, double* weight_coefficients);

/**
 * Perform all fusion algorithm steps and get the final fused value.
 * @param sensors The sensors list vector.
 * @param p The contribution parameter p.
 * @param tolerance The fault tolerance value.
 * @return The fused output for all sensors.
 */
double perform_sensor_fusion(SensorsList_t sensors, float p, float tolerance);


#endif /* FUSION_ALGORITHM_HPP_ */
