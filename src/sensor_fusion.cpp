
/** @file source_fusion.cpp
 * @brief The main function for the Sensor Fusion Project.
 */

// All C++ Headers
#include <iostream>
#include "../inc/sf_common.hpp"
#include "../inc/sf_impl.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here

#ifdef __cplusplus
}
#endif

void print_usage()
{
//TODO: fill this

}

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    printf("Program Name: %s\n", argv[0]);
    printf("Number of arguments: %d\n", argc);
    //TODO: ask user to provide column data in file

    int ret = 0;
    if (1 == argc)
    {
        print_usage();
        return 0;
    }
    else if (2 == argc)
    {
        /**
         *         argv[1] is assumed to be a filename to open.
         *         If only the file name is provided default values will be used:
         *
         *         sensos_stuck_interval default is: 10 minutes
         *         fusion_interval_minutes default is: 2 minutes
         */
        ret = parse_file(argv[1]);
        return ret;
    }
    else if (3 == argc)
    {
        /**
         *         argv[2] is assumed to be a elapsed time to determine if a sensor is stuck.
         *         argv[2] is validated to check if the values entered are digits.
         *         argv[2] is validated if it is within range (0 to 59 minutes).
         *         fusion_interval_minutes default value is used here: 2 minutes
         */

        if (0 == are_digits(argv[2]))
        {
            int sensos_stuck_interval = validate_interval(argv[2]);
            if (-1 != sensos_stuck_interval)
            {
                ret = parse_file(argv[1],
                                 sensos_stuck_interval);
                return ret;
            }
        }
    }
    else if (4 == argc)
    {
        /**
         *         argv[2] is assumed to be a elapsed time (in minutes) to determine if a sensor is stuck
         *         argv[3] is a tolerance range (in minutes) to fuse sensors within that range
         *
         *         argv[2] and argv[3] are validated to check if the values entered are digits
         *         argv[2] and argv[3] are validated if it is within range (0 to 59 minutes).
         */

        if (0 == are_digits(argv[2]) && 0 == are_digits(argv[3]))
        {
            int sensos_stuck_interval = validate_interval(argv[2]);
            int fusion_interval = validate_interval(argv[3]);

            if (-1 != fusion_interval && -1 != sensos_stuck_interval)
            {
                ret = parse_file(argv[1],
                                 sensos_stuck_interval,
                                 fusion_interval);
                return ret;
            }
        }
    }
    else
    {
        printf("Incorrect number of arguments\n");
        print_usage();
    }
    return 0;
}
