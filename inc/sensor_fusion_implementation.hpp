
/** @file sf_impl.hpp
 * Contains the declarations for the sensor fusion implementation
 */

#ifndef SF_IMPL_HPP_
#define SF_IMPL_HPP_

// All C++ Headers
#include "sensor_fusion_common.hpp"

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
 * @param contribution_p The p parameter used in contribution rate selection.
 * @param tolerance The tolerance ratio used in fault tolerance elimination process.
 * @param sensor_stuck_interval_minutes The minimum interval where if a sensor doesn't change value it's considered stuck.
 * @param fusion_interval_minutes The maximum interval where sensor values are fused.
 * @return A matrix with all sensor values. Each row represents all sensor values at
 * a specific timestamp.
 */
int parse_file(char *file_name, float contribution_p, float tolerance, int sensor_stuck_interval_minutes = 10,
               int fusion_interval_minutes = 2, char* output_file_path = "../data/fused_outputs.csv");

/**
 * Eliminate sensors that are not supported by more than q% of the sensors,
 * where q is the tolerance percentage, according to the theory of fault tolerance.
 * @param tolerance The tolerance percentage.
 * @param sensor_values The sensor values.
 */

int validate_interval(const char *string);

void check_sensor_stuck(ValidationList_t *list, int interval);

int compare_sensors_times(Sensor_t *sensor, Sensor_t *sensor2, int interval);

void test_bench();

int output_file(char *filename, char *content);


#endif /* SF_IMPL_HPP_ */
