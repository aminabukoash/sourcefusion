/** @file sf_impl.hpp
 * Contains the declarations for the sensor fusion implementation
 */

#ifndef SF_IMPL_HPP_
#define SF_IMPL_HPP_

// All C++ Headers
#include "../inc/sf_common.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here

#ifdef __cplusplus
}
#endif

//File parsing I/O declarations

Sensor_t create_sensor_from_line(char *sensorInfo);
//TODO: adjust comment accordingly
/**
 * Parse the input file and retrieve sensor values.
 * @param filename The name of the input file.
 * @return A matrix with all sensor values. Each row represents all sensor values at
 * a specific timestamp.
 */
int parse_file(char *file_name,
               int sensor_stuck_interval_minutes = 10,
               int fusion_interval_minutes = 2);

/**
 * Eliminate sensors that are not supported by more than q% of the sensors,
 * where q is the tolerance percentage, according to the theory of fault tolerance.
 * @param tolerance The tolerance percentage.
 * @param sensor_values The sensor values.
 */

int validate_interval(const char *string);

void check_sensor_stuck(StuckOrNotList_t *list,
                        int interval);

int compare_sensors_times(Sensor_t *sensor,
                          Sensor_t *sensor2,
                          int interval);

void test_bench();

/**
 * Output a given string to a text file.
 * @param filename The name of the output file.
 * @param content
 * @return
 */
int output_file(char *filename,
                char *content);


// validation declarations

/**
 * Validate the values of sensors at all times to make sure they're not stuck.
 * Output the names of the stuck sensors to a text file.
 * @param sensor_values
 */
void validate_times(float **sensor_values);


#endif /* SF_IMPL_HPP_ */
