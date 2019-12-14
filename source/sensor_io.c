#include <stdio.h>
#include <errno.h>
#include "../include/sensor_io.h"
#include "utils.c"

char line[128] = "";
struct sensor *sensors;
char **data;
char previous_time[7] = "";
int sensor_count = 0;
int time_count = -1;
char is_out_of_range = 0;

int output_file(char *filename, char *content) {
    return 1;
}

void structure_data(int n, int last_line){

    if(strcmp(data[0], previous_time) == 0){
        strcpy(sensors[time_count].data[sensor_count].sensor_name, data[1]);
        char* p_end;
        sensors[time_count].data[sensor_count].value = strtof(data[2], &p_end);
        strcpy(sensors[time_count].time, data[0]);
        sensors[time_count].size = sensor_count + 1;
        if (sensor_count > n){
            printf("Number of sensor on file is greater than max number of sensors passed");
            is_out_of_range = 1;
            return;
        }
        if (!last_line){
            sensor_count++;
        }

    } else {
        ++time_count;
        if (sensor_count > n){
            printf("Number of sensor on file is greater than max number of sensors passed\n");
            is_out_of_range = 1;
            return;
        }
        sensors = (struct sensor*)realloc(sensors, (time_count+1)* sizeof(struct sensor));
        sensors[time_count].data = (struct sensor_data*)malloc(n * sizeof(struct sensor_data));
        sensor_count = 0;
        strcpy(sensors[time_count].data[sensor_count].sensor_name, data[1]);
        char* p_end;
        sensors[time_count].data[sensor_count].value = strtof(data[2], &p_end);
        strcpy(sensors[time_count].time, data[0]);
        sensors[time_count].size = sensor_count + 1;

        if(!last_line){
            sensor_count++;
        }

    }

    strcpy(previous_time, data[0]);

    memset(line, 0, strlen(line));
}


struct sensor *parse_input(char *filename, int n) {

    FILE *input_file;
    char c;

    int line_number = 0;

    input_file = fopen(filename, "rt");

    if (input_file == NULL) {
        printf("File could not be opened: %s\n", strerror(errno));
        return NULL;
    } else {

        sensors = (struct sensor*)malloc(sizeof(struct sensor));
        sensors[0].data = (struct sensor_data*)malloc(n * sizeof(struct sensor_data));

        while ((c = fgetc(input_file)) != EOF) {
            if (c == '\n') {
                ++line_number;

                if (strlen(line) > 0){
                    data  =  str_split(line, ",");
                    structure_data(n, 0);
                    if (is_out_of_range){
                        return NULL;
                    }

                }

            }
            if (line_number > 0 && c != '\n') {
                char_concat(line, c);
            }
        }

        data  =  str_split(line, ",");
        structure_data(n, 1);
        if (is_out_of_range){
            return NULL;
        }

        return sensors;
    }

}
