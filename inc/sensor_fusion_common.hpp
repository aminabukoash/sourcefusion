
/** @file SfCommon.hpp
 *  @brief contains the common data structures used in the sensor fusion project
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

// Vector of sensor data: timestamp and value
typedef std::vector<std::pair<time_t, double>> SensorDataList_t;

// sensor status enum
typedef enum SensorStatus {
    SENSOR_STATUS_STUCK = 0,
    SENSOR_STATUS_ON,
    SENSOR_STATUS_UNKNOWN

} SensorStatus_t;

// Sensor state Information structure, this structure hold the Sensor Status Information
typedef struct SensorStateInfo {
    SensorStatus_t status = {SensorStatus_t::SENSOR_STATUS_UNKNOWN}; /**< sensor status*/
    SensorDataList_t data; /**< sensor data vector*/
} SensorStateInfo_t;

// Sensor structure
typedef struct Sensor {
    char name[SENSOR_MAX_NAME_LEN] = {'\0'}; /**< sensor name > **/
    time_t time; /**< sensor timestamp > **/
    double value; /**< sensor value > **/
} Sensor_t;

// Vector list of sensors
typedef std::vector<Sensor_t> SensorsList_t;


// Vector list of SensorList_t, for each SensorList_t (index) we will perform the fusion algorithm separately
typedef std::vector<SensorsList_t> FusionList_t;

//map to validate if sensor is stuck or not
typedef std::map<string, SensorStateInfo> ValidationList_t;


time_t make_time(const char *time);

char *get_field(const char *line,
                int num);

int are_digits(const char *string);

void print_time(time_t time);

#endif /* SF_COMMON_HPP_ */
