/*
 * sf_impl.cpp
 *
 */

// All C++ Headers
#include "../inc/sf_impl.hpp"

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
        SensorsList_t2 sensorList;
        FusionList_t fusionList;
        StuckOrNotList_t sutckornotlist;

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
                    //Handle stuckornot list
                    auto it = sutckornotlist.find(sensor.name);

                    if (it != sutckornotlist.end())
                    {
                        printf("sensor: %s found with value %f\n",
                               sensor.name,
                               sensor.value);

                        it->second.data.push_back(make_pair(sensor.time,
                                                            sensor.value));
//                        char time_buffer[100];
//                        strftime(time_buffer,
//                                 sizeof(time_buffer),
//                                 "Time in sensor data is %H:%M\n",
//                                 localtime(&sensor.time));
//
//                        printf(time_buffer);
                    }
                    else
                    {
                        SensorDataList_t dataList;
                        SensorStuckInfo_t sensorInfo;
                        printf("sensor: %s not found. Adding to stuckornot\n",
                               sensor.name);

                        dataList.push_back(make_pair(sensor.time,
                                                     sensor.value));

                        sensorInfo.data = dataList;
                        sutckornotlist.insert(make_pair(sensor.name,
                                                        sensorInfo));
                    }

                    // handle sensor fusion lists
                    int compare_status =
                            compare_sensors_times(&sensorList[0],
                                                  &sensor,
                                                  fusion_interval_minutes);

                    if (APPEND == compare_status)
                    {
                        sensorList.push_back(sensor);
                        //TODO: should we check for duplicates?
                        // How do we bloody handle them?
                    }
                    else
                    {
                        // push the sensor to the Fusion List
                        fusionList.push_back(sensorList);
                        // Clear it to start a new sensorList
                        sensorList.clear();
                        // Push the sensor to the new list
                        sensorList.push_back(sensor);
                    }
                }
                else
                {
                    printf("Brand new list, adding sensor\n");
                    sensorList.push_back(sensor);

                    SensorDataList_t dataList;
                    SensorStuckInfo_t sensorInfo;
                    printf("sensor: %s not found. Adding to stuckornot\n",
                           sensor.name);

                    dataList.push_back(make_pair(sensor.time,
                                                 sensor.value));

                    sensorInfo.data = dataList;
                    sutckornotlist.insert(make_pair(sensor.name,
                                                    sensorInfo));
                }
                free(sensorInfo);
            }
        }
        fclose(file);

        check_sensor_stuck(&sutckornotlist,
                           sensor_stuck_interval_minutes);
    }

    return SUCCESS;
}

int validate_interval(const char *string)
{
    int value = atoi(string);
    if (!(0 <= value && value < 60))
    {
        printf("Interval value entered is out of range, please enter a value from 0 to 59 in minutes");
        return -1;
    }
    return value;
}

void check_sensor_stuck(StuckOrNotList_t *list,
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

    printf("diff in seconds? %f\n", diff_in_seconds);

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

void validate_values(float tolerance,
                     float **sensor_values)
{
    //TODO: Implement this
}

