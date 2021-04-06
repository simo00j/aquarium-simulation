#ifndef __FISH__H__
#define __FISH__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_MAX_SIZE 60
#define COMMAND_MAX_SIZE 20
#define MAX_NAME_SIZE 30
#define ARGS_MAX_SIZE (INPUT_MAX_SIZE - COMMAND_MAX_SIZE)
#define DEBUG 1
#define DEBUG_OUT(...)                    \
    do                                    \
    {                                     \
        if (DEBUG)                        \
            fprintf(stderr, __VA_ARGS__); \
    } while (0)






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


typedef struct fish
{
    char name[MAX_NAME_SIZE];
    size size;
    position position;
    pathWay path_function;

} fish;

void addFish( char* name, ,size s, );
void startFish(char* name);
void delFish(char* name);
void getFishes();
void getFishesContinuously();


#endif //__FISH__H__