
/** @file sensor_fusion_common.hpp
 *  @brief contains the common data structures used in the sensor fusion project
 *
 *  Contains the common data structures and type definitions used in the rest of the project.
 */

#ifndef SF_COMMON_HPP_
#define SF_COMMON_HPP_


// All C++ Headers
#include <iostream>
#include<map>
#include<vector>

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_blas.h>

#ifdef __cplusplus
}
#endif
using namespace std;

#define SUCCESS 0
#define FAIL -1
#define NEW_LIST 1
#define APPEND 0

#define SENSOR_MAX_NAME_LEN  46
#define SENSOR_MAX_TIME_LEN 8

#define OUTPUT_FILE_NAME "../data/fused_outputs.csv"

/**
 * @typedef Vector of sensor data: timestamp and value.
 */
typedef std::vector<std::pair<time_t, double>> SensorDataList_t;

/**
 * @enum Sensor status enum
 */
typedef enum SensorStatus {
    SENSOR_STATUS_STUCK = 0,
    SENSOR_STATUS_ON,
    SENSOR_STATUS_UNKNOWN

} SensorStatus_t;

/**
 * @typedef Sensor state Information structure, this structure hold the Sensor Status Information.
 */
typedef struct SensorStateInfo {
    SensorStatus_t status = {SensorStatus_t::SENSOR_STATUS_UNKNOWN}; /**< sensor status*/
    SensorDataList_t data; /**< sensor data vector*/
} SensorStateInfo_t;

/**
 * @struct Structure to hold sensor information.
 */
typedef struct Sensor {
    char name[SENSOR_MAX_NAME_LEN] = {'\0'}; /**< sensor name > **/
    time_t time; /**< sensor timestamp > **/
    double value; /**< sensor value > **/
} Sensor_t;

/**
 * @typedef Vector list of Sensors.
 */
typedef std::vector<Sensor_t> SensorsList_t;


/**
 * @typedef Map to validate if the sensor is stuck or not.
 */
typedef std::map<string, SensorStateInfo> ValidationList_t;

/**
 * @brief Creates time_t instance from char pointer.
 *
 * Create the corresponding time_t instance from a character string by deconstructing the time string and extracting time components.
 * @param time The time character string
 * @return The corresponding time_t instance.
 */
time_t make_time(const char *time);

/**
 * @brief Get the corresponding field from the character line.
 *
 * Gets the corresponding field value from a comma separated line according to the provided field index.
 * @param line The character line.
 * @param num The index of the required field.
 * @return The field value.
 */
char *get_field(const char *line, int num);

/**
 * @brief Checks if the  string is a valid number.
 *
 * Checks if the provided string consists of valid number digits or not.
 * @param string The string to be validated.
 * @return 0 if it's a valid number, -1 if it's not valid.
 */
int are_digits(const char *string);

#endif /* SF_COMMON_HPP_ */
