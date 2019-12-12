/** @file sensor_io.h
 * Contains the declarations for the file input/output functions.
 */

#ifndef __SENSOR_IO_H__
#define __SENSOR_IO_H__


struct sensor_data {
    char sensor_name[20];
    float value;
};

struct sensor{
    char time[7];
    struct sensor_data* data;
    int size;
};
/**
 * Output a given string to a text file.
 * @param filename The name of the output file.
 * @param content
 * @return
 */
int output_file(char* filename, char* content);

/**
 * Parse the input file and retrieve sensor values.
 * @param filename The name of the input file.
 * @return A matrix with all sensor values. Each row represents all sensor values at
 * a specific timestamp.
 */
struct sensor* parse_input(char* filename, int n);

#endif /* __SENSOR_IO_H__ */
