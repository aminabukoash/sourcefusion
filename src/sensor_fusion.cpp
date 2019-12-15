
/** @file source_fusion.cpp
 * @brief The main function for the Sensor Fusion Project.
 */

// All C++ Headers
#include <iostream>
#include "../inc/sensor_fusion_common.hpp"
#include "../inc/sensor_fusion_implementation.hpp"
#include "../inc/fusion_algorithm.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here

#ifdef __cplusplus
}
#endif

void print_usage() {
    printf("Usage: filename contribution_p tolerance stuck_interval fusion_interval\n");
    printf("\n");
    printf("  filename              : The name of the file with the input values. (required)\n");
    printf("  contribution_p        : The p parameter used in contribution rate selection.\n");
    printf("  tolerance             : The tolerance ratio used in fault tolerance elimination process.\n");
    printf("  stuck_interval        : The minimum interval where if a sensor doesn't change value it's considered stuck. (default = 10)\n");
    printf("  fusion_interval       : The maximum interval where sensor values are fused. (default = 2)\n");
    printf("\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    printf("Program Name: %s\n", argv[0]);
    printf("Number of arguments: %d\n", argc);
    //TODO: ask user to provide column data in file

    int ret = 0;
    char *filename;
    float contribution_p = 0.85, tolerance = 0.7;
    int stuck_interval = 10, fusion_interval = 2;


    /**
     * Usage: filename contribution_p tolerance stuck_interval fusion_interval.
     *   filename              : The name of the file with the input values. (required)
     *   contribution_p        : The p parameter used in contribution rate selection. Default = 0.85.
     *   tolerance             : The tolerance ratio used in fault tolerance elimination process. Default = 0.7.
     *   stuck_interval        : The minimum interval where if a sensor doesn't change value it's considered stuck.
     *                          Acceptable range is from 0 to 59 minutes. Default = 10.
     *   fusion_interval       : The maximum interval where sensor values are fused. Default = 2.
     */

    if (argc == 1) {
        print_usage();
        return 0;
    }else if(argc > 6){
        printf("Incorrect number of arguments\n");
        print_usage();
        return 0;
    }

    if (argc >= 2) {
        filename = argv[1];
    }
    if (argc >= 3) {
        contribution_p = atoi(argv[2]);
    }
    if (argc >= 4) {
        tolerance = atoi(argv[3]);
    }
    if (argc >= 5) {
        if (are_digits(argv[4]) == 0) {

            int sensor_stuck_interval = validate_interval(argv[4]);

            if (-1 != sensor_stuck_interval) {
                stuck_interval = sensor_stuck_interval;
            }
        }
    }
    if (argc == 6) {
        if (are_digits(argv[5]) == 0) {

            int sensor_fusion_interval = validate_interval(argv[5]);

            if (sensor_fusion_interval != -1) {
                fusion_interval = sensor_fusion_interval;
            }
        }
    }

    ret = parse_file(filename, contribution_p, tolerance, stuck_interval, fusion_interval);
    return ret;
}
