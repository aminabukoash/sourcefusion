
/** @file sf_impl.cpp
 *  @brief contains the common functions used in the sensor fusion project.
 */

// All C++ Headers
#include "../inc/sensor_fusion_common.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// All C Headers go here

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
    bool point_seperated = false;
    int length = strlen(time);

    for (int i = 0; i < length; i++)
    {
        if (strchr(".", *time))
        {
            point_seperated = true;
        }
    }

    if (point_seperated)
    {
        sscanf(time, "%d.%d", &hours, &minutes);
    }
    else
    {
        sscanf(time, "%d:%d", &hours, &minutes);
    }

    tm.tm_hour = hours;
    tm.tm_min = minutes;
    tm.tm_sec = 0;
    tm.tm_isdst = 0;
    time_value = mktime(&tm);

    if (time_value == -1)
    {
        printf("unable to make time\n");
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
        {
            break;
        }
        p += len;
        if (*p == ',')
        {
            p++;
        }
    }
    res = (char*) malloc(len + 1);
    if (res)
    {
        memcpy(res, p, len);
        res[len] = '\0';
    }
    return res;
}

int are_digits(const char *string)
{
    int length = strlen(string);

    for (int i = 0; i < length; i++)
    {
        if (!isdigit(string[i]))
        {
            printf("Value: %s entered is not a valid number!", string);
            return -1;
        }
    }
    return 0;
}
