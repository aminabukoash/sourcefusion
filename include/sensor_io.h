/** @file sensor_io.h
 * Contains the declarations for the file input/output functions.
 */

#ifndef SENSOR_IO_H_
#define SENSOR_IO_H_

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
float** parse_input(char* filename);

#endif /* SENSOR_IO_H_ */
