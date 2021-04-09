#ifndef __AQUARIUM__H__
#define __AQUARIUM__H__


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
    fish **fish;
    int fish_number;
    view **views;
    int views_number; 
} aquarium;

aquarium *getDataFromFile(char *filepath);

#endif //__AQUARIUM__H__