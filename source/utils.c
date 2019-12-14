//
// Created by Chidiebere Onyedinma on 2019-12-12.
//
#include <stdlib.h>
#include <string.h>
#include "../include/utils.h"


void char_concat(char *dest, char src) {

    int size = strlen(dest);
    dest[size] = src;
    dest[size + 1] = '\0';

}

char ** str_split(char *str, char * delim) {
    char ** sub_str = malloc(3 * sizeof(char*));

    char *ptr = strtok(str, delim);

    for (int i =0 ; i < 3; ++i){
        sub_str[i] = malloc(20 * sizeof(char));
    }

    int i = 0;

    while (ptr != NULL)
    {

        sub_str[i] = ptr;
        i++;

        ptr = strtok(NULL, delim);
    }

    return sub_str;
}
