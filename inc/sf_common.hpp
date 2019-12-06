/*
 * SfCommon.hpp
 *
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

#ifdef __cplusplus
}
#endif
using namespace std;

#define SUCCESS 0
#define FAIL -1

#define SENSOR_MAX_NAME_LEN  46
#define SENSOR_MAX_TIME_LEN 8

// Map of sensor data: time and value
typedef std::map<time_t, double> SensorDataMap_t;

typedef enum SensorStatus
{

    SENSOR_STATUS_STUCK = 0,
    SENSOR_STATUS_ON,
    SENSOR_STATUS_UNKNOWN

} SensorStatus_t;

typedef struct Sensor
{
    char name[SENSOR_MAX_NAME_LEN] = { '\0' }; /**< sensor name*/
    SensorStatus_t status = { SensorStatus_t::SENSOR_STATUS_UNKNOWN }; /**< sensor status*/
    SensorDataMap_t data; /**< sensor data map*/
} Sensor_t;

// Vector list of sensors
typedef std::vector<Sensor_t> SensorsList_t;

time_t make_time(const char *time);

char* get_field(const char *line,
               int num);


#endif /* SF_COMMON_HPP_ */
