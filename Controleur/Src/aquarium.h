#ifndef __AQUARIUM__H__
#define __AQUARIUM__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fish.h"

typedef struct view
{
    char name[3];
    position position;
    size size;
} view;

typedef struct aquarium
{
    size size;
    int views_number;
    int fish_number;
    fish **fish;
    view **views;
} aquarium;

aquarium *getDataFromFile(char *filepath);

#endif //__AQUARIUM__H__