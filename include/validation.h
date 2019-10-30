/** @file fusion_algorithm.h
 * Contains the declarations for the input validation functions.
 */

#ifndef VALIDATION_H_
#define VALIDATION_H_

/**
 * Validate the values of sensors at all times to make sure they're not stuck.
 * Output the names of the stuck sensors to a text file.
 * @param sensor_values
 */
void validate_times(float** sensor_values);

/**
 * Eliminate sensors that are not supported by more than q% of the sensors,
 * where q is the tolerance percentage, according to the theory of fault tolerance.
 * @param tolerance The tolerance percentage.
 * @param sensor_values The sensor values.
 */
void validate_values(float tolerance, float** sensor_values);

#endif /* VALIDATION_H_ */
