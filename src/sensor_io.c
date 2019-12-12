#include <stdio.h>
#include <errno.h>
#include "../include/sensor_io.h"
#include "utils.c"

int output_file(char *filename, char *content) {
    return 1;
}


struct sensor *parse_input(char *filename, int n) {

    FILE *input_file;
    char c;
    char line[128] = "";
    int line_number = 0;

    struct sensor *sensors;


    input_file = fopen(filename, "rt");

    if (input_file == NULL) {
        printf("File could not be opened: %s\n", strerror(errno));
        return NULL;
    } else {

        char **data;
        char previous_time[7] = "";
        int sensor_count = 0;
        int time_count = -1;

        sensors = (struct sensor*)malloc(sizeof(struct sensor));
        sensors[0].data = (struct sensor_data*)malloc(n * sizeof(struct sensor_data));

        while ((c = fgetc(input_file)) != EOF) {
            if (c == '\n') {
                ++line_number;

                if (strlen(line) > 0){
                  data  =  str_split(line, ",");

                  if(strcmp(data[0], previous_time) == 0){
                      strcpy(sensors[time_count].data[sensor_count].sensor_name, data[1]);
                      char* p_end;
                      sensors[time_count].data[sensor_count].value = strtof(data[2], &p_end);
                      strcpy(sensors[time_count].time, data[0]);
                      sensors[time_count].size = sensor_count + 1;
                      sensor_count++;
                  } else {
                      ++time_count;
                      sensors = (struct sensor*)realloc(sensors, (time_count+1)* sizeof(struct sensor));
                      sensors[time_count].data = (struct sensor_data*)malloc(n * sizeof(struct sensor_data));
                      sensor_count = 0;
                      strcpy(sensors[time_count].data[sensor_count].sensor_name, data[1]);
                      char* p_end;
                      sensors[time_count].data[sensor_count].value = strtof(data[2], &p_end);
                      strcpy(sensors[time_count].time, data[0]);
                      sensors[time_count].size = sensor_count + 1;
                      sensor_count++;
                  }

                  strcpy(previous_time, data[0]);

                  memset(line, 0, strlen(line));

                }

            }
            if (line_number > 0 && c != '\n') {
                char_concat(line, c);
            }
        }

        data  =  str_split(line, ",");

        if(strcmp(data[0], previous_time) == 0) {
            strcpy(sensors[time_count].data[sensor_count].sensor_name, data[1]);
            char* p_end;
            sensors[time_count].data[sensor_count].value = strtof(data[2], &p_end);
            strcpy(sensors[time_count].time, data[0]);
            sensors[time_count].size = sensor_count + 1;
        } else {
            ++time_count;
            sensors = (struct sensor*)realloc(sensors, (time_count+1)* sizeof(struct sensor));
            sensors[time_count].data = (struct sensor_data*)malloc(n * sizeof(struct sensor_data));
            sensor_count = 0;
            strcpy(sensors[time_count].data[sensor_count].sensor_name, data[1]);
            char* p_end;
            sensors[time_count].data[sensor_count].value = strtof(data[2], &p_end);
            strcpy(sensors[time_count].time, data[0]);
            sensors[time_count].size = sensor_count + 1;
        }

        strcpy(previous_time, data[0]);

        memset(line, 0, strlen(line));

        return sensors;
    }

}
