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

#ifdef __cplusplus
}
#endif

Sensor_t create_sensor_from_line(char *sensorInfo)
{
    Sensor_t sensor;
    //TODO: remove debug lines
    printf("Field 1 is time would be %s\n", get_field(sensorInfo, 1));
    printf("Field 2 is name %s\n", get_field(sensorInfo, 2));
    printf("Field 3 is value %s\n", get_field(sensorInfo, 3));

    strncpy(sensor.name,
            get_field(sensorInfo, 2),
            sizeof(sensor.name));

    time_t time_value;
    time_value = make_time(get_field(sensorInfo, 1));
    double value = atof(get_field(sensorInfo, 3));
    sensor.data.insert(std::pair<time_t, double>(time_value,
                                                 value));
    //TODO: create sensor
    return sensor;

}

int parse_file(char *file_name)
{
    printf("Program Name Is: %s\n", file_name);
    //TODO: handle bad file names

    FILE *file = fopen(file_name, "r");

    /* fopen returns 0, the NULL pointer, on failure */
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
                            //TODO:Remove Debug line
                            printf("Found sensor in list name %s, appending value: %s and time %s\n",
                                   get_field(sensorInfo, 2),
                                   get_field(sensorInfo, 3),
                                   get_field(sensorInfo, 1));

                            time_t time_value;
                            time_value = make_time(get_field(sensorInfo, 1));

                            sensorFound = true;
                            double value = atof(get_field(sensorInfo, 3));
                            sensor.data.insert(std::pair<time_t, double>(time_value,
                                                                         value));
                        }
                    }
                }
                if (!sensorFound)
                {
                    sensor = create_sensor_from_line(sensorInfo);
                }
                sensorList.push_back(sensor);
                free(sensorInfo);
            }
        }
        fclose(file);
    }

    return SUCCESS;
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
