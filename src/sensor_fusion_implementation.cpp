
/** @file sf_impl.cpp
 *  @brief contains the implementations of the sensor fusion functions
 */

// All C++ Headers
#include <unistd.h>
#include "../inc/sensor_fusion_implementation.hpp"
#include "../inc/fusion_algorithm.hpp"

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

    char *OUTPUT_FILE_PATH = "../data/fused_outputs.csv";
    char DATA_PATH[9] = "../data/";
    char *input_file_path = strcat(DATA_PATH, file_name);
    FILE *file = fopen(input_file_path, "r");

    if (file == NULL)
    {
        printf("Error...\nCannot open file: %s\n", file_name);
        printf("Either the filename is incorrect or it does not exists.\n");
        return FAIL;
    }
    else
    {
        char line[1024];
        char time_str[20];
        int count = 0;
        char *not_reach_end;
        SensorsList_t sensorList;
        ValidationList_t validationList;

        //TODO: if invalid line.. print invalid data and continue;
        // at the end print the number of ignored data; maybe also print the line number in file.
        while (not_reach_end)
        {
            not_reach_end = fgets(line, 1024, file);
            count++;
            if (count != 1){
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

                    if(count == 3){
                        output_file(OUTPUT_FILE_PATH, "\nTime,Fused Value\n");
                    }

                    /**
                     * Handle sensor fusion lists here.
                     * Multiple Sensor lists (SensorsList_t) are created.
                     * Sensor fusion will be performed on each SensorList_t
                     *
                     */
                    int compare_status = compare_sensors_times(&sensorList[0], &sensor, fusion_interval_minutes);

                    if (compare_status == APPEND && not_reach_end)
                    {
                        strcpy(time_str, get_field(sensorInfo, 1));
                        sensorList.push_back(sensor);
                        //TODO: should we check for duplicate sensors?
                    }
                    else
                    {
                        // push the Sensor List to the Fusion List
                        double fused_output = perform_sensor_fusion(sensorList, contribution_p, tolerance);

                        char output[40];
                        sprintf(output, "%s,%f\n", time_str, fused_output);
                        output_file(OUTPUT_FILE_PATH, output);
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
                    printf("sensor: %s not found. Adding to SensorStateInfo_t\n", sensor.name);

                    dataList.push_back(make_pair(sensor.time, sensor.value));

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

void check_sensor_stuck(ValidationList_t *list, int interval)
{
    char *STUCK_FILE_PATH = "../data/stuck_sensors.txt";
    double diff_in_seconds = 0;

    for (auto it = list->begin(); it != list->end(); it++)
    {
        printf("checking sensor %s....\n", it->first.c_str());

        int size = it->second.data.size();
        for (int i = 0; i < size; ++i){
            if (size > 1){
                for (int j = i+1; j < size; ++j) {
                    if (it->second.data[i].second != it->second.data[j].second){
                        break;
                    }

                    diff_in_seconds = abs(difftime(it->second.data[j].first, it->second.data[i].first));

                    if ((diff_in_seconds / 60) > interval)
                    {
                        if (it->second.data[i].second == it->second.data[j].second)
                        {
                            char output[40];
                            sprintf(output, "Sensor %s is stuck with value %f\n", it->first.c_str(), it->second.data[i].second);
                            output_file(STUCK_FILE_PATH, output);

                            it->second.status = SensorStatus_t::SENSOR_STATUS_STUCK;
                        }
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

int compare_sensors_times(Sensor_t *sensor, Sensor_t *sensor2, int interval)
{
    double diff_in_seconds = 0;

        //TODO: handle problem if a new day occurs
    diff_in_seconds = difftime(sensor2->time,
                               sensor->time);

    printf("diff in minutes? %.0f\n", diff_in_seconds / 60);

    if ((diff_in_seconds / 60) > interval)
    {
        printf("Sensor %s is past the interval, adding to a new list\n", sensor2->name);
        return NEW_LIST;
    }
    else
    {
        printf("Sensor %s is within interval, appending to list \n", sensor2->name);
        return APPEND;

    }
}

void test_bench()
{

}

int output_file(char *filename, char *content){
    FILE *file_p;

    /*  Open file in append mode. */
    file_p = fopen(filename, "a");


    /* Create the file if it doesn't exist.*/
    if (file_p == NULL){

        file_p = fopen(filename, "w");
        if (file_p == NULL) {
            printf("\nUnable to create '%s' file.\n", filename);
            exit(EXIT_FAILURE);
        }
    }

    /* Append data to file */
    fputs(content, file_p);

    /* Done with file, hence close file. */
    fclose(file_p);

    return 0;
}

