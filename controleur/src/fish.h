#ifndef __FISH__H__
#define __FISH__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define INPUT_MAX_SIZE 60
#define COMMAND_MAX_SIZE 20
#define MAX_NAME_SIZE 30
#define MAX_TIME 100
#define ARGS_MAX_SIZE (INPUT_MAX_SIZE - COMMAND_MAX_SIZE)
#define DEBUG 1
#define DEBUG_OUT(...)                    \
    do                                    \
    {                                     \
        if (DEBUG)                        \
            fprintf(stderr, __VA_ARGS__); \
    } while (0)



typedef enum path_type{
    RANDOMWAYPOINT;
    ZIGZAG;
} path_type;


typedef struct position
{
    int x;
    int y;
} position;

typedef struct size
{
    int width;
    int height;
} size;

typedef struct PathWay
{
    position * (*path)(void*);
    position* T;
    int max_distance;



} PathWay;

typedef struct fish
{
    char name[MAX_NAME_SIZE];
    size size;
    position position;
    PathWay path;

} fish;

void addFish( char* name, position pos ,size s, PathWay p,aquarium *a );
void startFish(char* name, aquarium *a);
void delFish(char* name, aquarium *a);
void getFishes(aquarium *a);
void getFishesContinuously(aquarium *a);
void ls(aquarium *a);


#endif //__FISH__H__