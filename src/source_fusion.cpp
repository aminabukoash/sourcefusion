
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
    //Validate if number entered is valid, and not some random garbage

    //TODO: add custom

    int ret = 0;
    if (1 == argc)
    {
        print_usage();
        return 0;
    }
    else if (2 == argc)
    {
        // We assume argv[1] is a filename to open
        ret = parse_file(argv[1]);

        return ret;

    }
    else if (3 == argc)
    {
//TODO: Add time interval
    }
    else if (4 == argc)
    {
//TODO: Add custom tolerance form time
    }
    else
    {
        printf("Incorrect number of arguments\n");
        print_usage();
    }

    return 0;
}