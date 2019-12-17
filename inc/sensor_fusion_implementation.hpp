
/** @file sensor_fusion_implementation.hpp
 * @brief Fusion top level function.
 *
 * Contains the declarations for the sensor input parsing and output functions.
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


Sensor_t create_sensor_from_line(char *sensorInfo);

/**
 * @brief Parse the input file and call the fusion function to fuse the values.
 *
 * Parse the input file provided in the data folder and retrieve all sensor values, then perform the fusion algorithm and output the results .
 * @param filename The name of the input file.
 * @param contribution_p The p parameter used in contribution rate selection.
 * @param tolerance The tolerance ratio used in fault tolerance elimination process.
 * @param sensor_stuck_interval_minutes The minimum interval where if a sensor doesn't change value it's considered stuck.
 * @param fusion_interval_minutes The maximum interval where sensor values are fused.
 * @return 0 if fusion was successful, -1 if it failed.
 */
int parse_file(char *file_name, float contribution_p, float tolerance, int sensor_stuck_interval_minutes = 10,
               int fusion_interval_minutes = 2, char* output_file_path = "../data/fused_outputs.csv");

/**
 * @brief Check if the value is within range.
 *
 * Check that the string is a valid number that falls in the acceptable range.
 * @param string The number string.
 * @return The integer value if the string valid nad -1 otherwise.
 */
int validate_interval(const char *string);

/**
 * @brief Chek for stuck sensors.
 *
 * Check if the sensor is stuck at the same value for a given range.
 * @param list List of sensors and the values.
 * @param interval The interval in minutes where if the value doesn't change, the sensor is considered stuck.
 */
void check_sensor_stuck(ValidationList_t *list, int interval);

/**
 * @brief Check if the sensor times need to be fused.
 *
 * Compares times between two consecutive sensor values to check if they should be fused or not.
 * @param sensor The first sensor instance that holds time and value.
 * @param sensor2 The first sensor instance that holds time and value.
 * @param interval The maximum time interval to be fused in minutes.
 * @return 0 if sensors are to be fused, 1 if the second sensor will be fused in the next list.
 */
int compare_sensors_times(Sensor_t *sensor, Sensor_t *sensor2, int interval);

/**
 * @brief Outputs the provided string to a file.
 *
 * Outputs the provided string content to a specified file and creates a new file according to the writing mode provided.
 * @param filename The name of the file where the content will be written.
 * @param content The string content that will be written to the file.
 * @param mode The writing mode. It can be append or a new file.
 * @return -1 if the file couldn't be opened, 0 if the content was outputted successfully.
 */
int output_file(char *filename, char *content, int mode);


#endif /* SF_IMPL_HPP_ */
