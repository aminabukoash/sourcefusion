
/** @file sf_impl.cpp
 *  @brief contains the implementations of the sensor fusion functions
 */

// All C++ Headers
#include "../inc/sensor_fusion_implementation.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here
#include <ctype.h>

#ifdef __cplusplus
}
#endif

Sensor_t create_sensor_from_line(char *sensorInfo)
{
    Sensor_t sensor;

    strncpy(sensor.name,
            get_field(sensorInfo, 2),
            sizeof(sensor.name));

    sensor.time = make_time(get_field(sensorInfo, 1));
    sensor.value = atof(get_field(sensorInfo, 3));

    return sensor;
}

int parse_file(char *file_name,
               float contribution_p,
               float tolerance,
               int sensor_stuck_interval_minutes,
               int fusion_interval_minutes)
{
    printf("Minutes passed to determine if sensor is stuck interval: %d\n",
           sensor_stuck_interval_minutes);
    printf("fusion interval: %d\n", fusion_interval_minutes);

    FILE *file = fopen(file_name, "r");

    if (NULL == file)
    {
        printf("Error...\nCannot open file: %s\n", file_name);
        printf("Either the filename is incorrect or it does not exists.\n");
        return FAIL;
    }
    else
    {
        char line[1024];
        int count = 0;
        SensorsList_t sensorList;
        FusionList_t fusionList;
        ValidationList_t validationList;

        //TODO: if invalid line.. print invalid data and continue;
        // at the end print the number of ignored data; maybe also print the line number in file.
        while (fgets(line, 1024, file))
        {
            count++;
            if (1 != count)
            {
                Sensor_t sensor;
                char *sensorInfo = strdup(line);
                sensor = create_sensor_from_line(sensorInfo);
                if (!sensorList.empty())
                {
                    /**
                     * Handle validation list here.
                     * Validation list will be used to check if a sensor is stuck or not.
                     */
                    auto it = validationList.find(sensor.name);

                    if (it != validationList.end())
                    {

                        /**
                         * if the sensor is found, we push the new data to the SensorDataList_t
                         */

                        printf("\nsensor: %s found with value %.0f\n",
                               sensor.name,
                               sensor.value);

                        it->second.data.push_back(make_pair(sensor.time,
                                                            sensor.value));
                    }
                    else
                    {

                        /**
                         * if the sensor is not found found:
                         *  - A SensorDataList_t is created and pushed to data in SensorState_Info_t
                         *  - SensorStateInfo_t is created and pushed into the ValidationList_t
                         */

                        SensorDataList_t dataList;
                        SensorStateInfo_t sensorInfo;
                        printf("sensor: %s not found. Adding new sensor..\n",
                               sensor.name);

                        dataList.push_back(make_pair(sensor.time,
                                                     sensor.value));

                        sensorInfo.data = dataList;
                        validationList.insert(make_pair(sensor.name,
                                                        sensorInfo));
                    }

                    /**
                     * Handle sensor fusion lists here.
                     * Multiple Sensor lists (SensorsList_t) are created.
                     * Sensor fusion will be performed on each SensorList_t
                     *
                     */
                    int compare_status =
                            compare_sensors_times(&sensorList[0],
                                                  &sensor,
                                                  fusion_interval_minutes);

                    if (APPEND == compare_status)
                    {
                        sensorList.push_back(sensor);
                        //TODO: should we check for duplicate sensors?
                    }
                    else
                    {
                        // push the Sensor List to the Fusion List
                        fusionList.push_back(sensorList);
                        // Clear it to start a new sensorList
                        sensorList.clear();
                        // Push the sensor to the new list
                        sensorList.push_back(sensor);
                    }
                }
                else // sensorList.empty()
                {
                    printf("New Sensor list, adding sensor\n");
                    sensorList.push_back(sensor);

                    SensorDataList_t dataList;
                    SensorStateInfo_t sensorInfo;
                    printf("sensor: %s not found. Adding to SensorStateInfo_t\n",
                           sensor.name);

                    dataList.push_back(make_pair(sensor.time,
                                                 sensor.value));

                    sensorInfo.data = dataList;
                    validationList.insert(make_pair(sensor.name,
                                                    sensorInfo));
                }
                free(sensorInfo);
            }
        }
        fclose(file);

        // checking if any sensors are stuck
        check_sensor_stuck(&validationList,
                           sensor_stuck_interval_minutes);
    }

    return SUCCESS;
}

int validate_interval(const char *string)
{
    //TODO: accept different range for fusion and for stuck
    int value = atoi(string);
    if (!(0 <= value && value < 60))
    {
        printf("Interval value entered is out of range, please enter a value from 0 to 59 in minutes");
        return -1;
    }
    return value;
}

void check_sensor_stuck(ValidationList_t *list,
                        int interval)
{
    double diff_in_seconds = 0;

    for (auto it = list->begin(); it != list->end(); it++)
    {
        printf("checking sensor %s....\n", it->first.c_str());

        int size = it->second.data.size();
        for (int i = 1; i < size; ++i)
        {
            if (size > 1)
            {
                //TODO: handle problem if a new day occurs
                diff_in_seconds = difftime(it->second.data[i].first,
                                           it->second.data[i - 1].first);

                if ((diff_in_seconds / 60) > interval)
                {
                    if (it->second.data[i].second
                        == it->second.data[i - 1].second)
                    {
                        printf("Sensor %s is stuck with value %f\n",
                               it->first.c_str(),
                               it->second.data[i].second);

                        it->second.status = SensorStatus_t::SENSOR_STATUS_STUCK;
                    }
                }
            }
            else
            {
                it->second.status = SensorStatus_t::SENSOR_STATUS_ON;

            }
        }
    }
}

int compare_sensors_times(Sensor_t *sensor,
                          Sensor_t *sensor2,
                          int interval)
{
    double diff_in_seconds = 0;

        //TODO: handle problem if a new day occurs
    diff_in_seconds = difftime(sensor2->time,
                               sensor->time);

    printf("diff in minutes? %.0f\n", diff_in_seconds / 60);

    if ((diff_in_seconds / 60) > interval)
    {
        printf("Sensor %s is past the interval, adding to a new list\n",
               sensor2->name);
        return NEW_LIST;
    }
    else
    {
        printf("Sensor %s is within interval, appending to list \n",
               sensor2->name);
        return APPEND;

    }
}

void test_bench()
{

}

int output_file(char *filename,
                char *content)
{
    //TODO: Implement this
    return 0;
}

