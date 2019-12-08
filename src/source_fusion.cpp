
// All C++ Headers
#include <iostream>
#include "../inc/sf_common.hpp"
#include "../inc/sf_impl.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here
#include <stdio.h>
#include <stdlib.h>

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
    test_bench();
    printf("Program Name Is: %s\n", argv[0]);
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
        // We assume argv[1] is a filename to open

        //sensos_stuck_interval default is 10 minutes
        //fusion_interval_minutes default is 2 minutes

        ret = parse_file(argv[1]);
        return ret;
    }
    else if (3 == argc)
    {
        // We assume argv[2] is a number of minutes to determine if a sensor is stuck

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
        // We assume argv[3] is a range (in minutes) to fuse sensors within that range
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
