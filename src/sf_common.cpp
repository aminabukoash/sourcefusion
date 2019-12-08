// All C++ Headers
#include "../inc/sf_common.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
}
#endif

time_t make_time(const char *time)
{
    int hours, minutes;
    struct tm tm;
    tm.tm_year = 2020 - 1900;  // Years from 1900
    tm.tm_mon = 1 - 1; // Months form January
    tm.tm_mday = 1;
    time_t time_value;
    char time_buffer[100];

    sscanf(time, "%d:%d", &hours, &minutes);
    tm.tm_hour = hours;
    tm.tm_min = minutes;
    tm.tm_sec = 0;  // or simply = ss;
    tm.tm_isdst = 0;
    time_value = mktime(&tm);

    if (time_value == -1)
    {
        printf("unable to make time\n");
    }
    else
    {
        strftime(time_buffer,
                 sizeof(time_buffer),
                 "%H:%M\n",
                 &tm);
        printf(time_buffer);
    }
    return time_value;
}

char* get_field(const char *line,
               int num)
{
    const char *p = line;
    size_t len;
    char *res;
    for (;;)
    {
        len = strcspn(p, ",\n");
        if (--num <= 0)
            break;
        p += len;
        if (*p == ',')
            p++;
    }
    res = (char*) malloc(len + 1);
    if (res)
    {
        memcpy(res, p, len);
        res[len] = '\0';
    }
    return res;
}
