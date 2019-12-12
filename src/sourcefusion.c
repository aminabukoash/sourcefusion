#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include "sensor_io.c"
#include "../include/validation.h"
#include "../include/fusion_algorithm.h"

int main(int argc, char*argv[]) {

    struct sensor * all_sensors = parse_input(argv[1], atoi(argv[2]));

    printf("Sensor name: %s\n", all_sensors[0].data[1].sensor_name);

    return 0;
}
