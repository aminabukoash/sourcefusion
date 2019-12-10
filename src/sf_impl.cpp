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
    //TODO: remove debug lines
    printf("Field 1 is time  %s\n", get_field(sensorInfo, 1));
    printf("Field 2 is name %s\n", get_field(sensorInfo, 2));
    printf("Field 3 is value %s\n", get_field(sensorInfo, 3));

    strncpy(sensor.name,
            get_field(sensorInfo, 2),
            sizeof(sensor.name));

    time_t time_value;
    time_value = make_time(get_field(sensorInfo, 1));
    double value = atof(get_field(sensorInfo, 3));
    sensor.data.push_back(std::make_pair(time_value, value));

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
        SensorsList_t sensorList;
        FusionList_t fusionList;

        while (fgets(line, 1024, file))
        {
            bool sensorFound = false;
            count++;
            if (1 != count)
            {
                Sensor_t sensor;
                char *sensorInfo = strdup(line);
                if (!sensorList.empty())
                {
                    for (Sensor_t sensor : sensorList)
                    {
                        if (strcmp(get_field(sensorInfo, 2), sensor.name) == 0)
                        {
                            printf("Found sensor %s in list , appending values!\n",
                                   get_field(sensorInfo, 2));

                            time_t time_value;
                            time_value = make_time(get_field(sensorInfo, 1));

                            sensorFound = true;
                            double value = atof(get_field(sensorInfo, 3));
                            sensor.data.push_back(std::make_pair(time_value,
                                                                 value));

                            //TODO: remove debugging loop
                            for (auto itr : sensor.data)
                            {
                                char time_buffer[100];
                                strftime(time_buffer,
                                         sizeof(time_buffer),
                                         "Time in sensor data is %H:%M\n",
                                         localtime(&itr.first));
                                printf(time_buffer);
                            }
                            //TODO: move check to a more appropriate place for efficiency
                            check_sensor_stuck(&sensor,
                                               sensor_stuck_interval_minutes);
                        }
                    }
                }
                if (!sensorFound)
                {
                    sensor = create_sensor_from_line(sensorInfo);
                    sensorList.push_back(sensor);
                }
                free(sensorInfo);
            }
        }
        fclose(file);
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

void check_sensor_stuck(Sensor_t *sensor,
                        int interval)
{
    double diff_in_seconds = 0;
    for (uint32_t i = 1; i < sensor->data.size(); ++i)
    {
        //TODO: handle problem if a new day occurs
        diff_in_seconds = difftime(sensor->data[i].first,
                                   sensor->data[i - 1].first);

        printf("diff in seconds? %f\n", diff_in_seconds);

        if ((diff_in_seconds / 60) > interval)
        {
            printf("Sensor %s is stuck\n", sensor->name);
            //TODO: what if it gets unstuck?
            sensor->status = SensorStatus_t::SENSOR_STATUS_STUCK;
        }
    }

}

void test_bench()
{
    //    char *time = strdup(get_field(sensorInfo, 1));
}

int output_file(char *filename,
                char *content)
{
    //TODO: Implement this
    return 0;
}

void validate_times(float **sensor_values)
{
    //TODO: Implement this
}

void validate_values(float tolerance,
                     float **sensor_values)
{
    //TODO: Implement this
}


