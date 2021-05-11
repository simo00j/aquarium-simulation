#ifndef FISH_H
#define FISH_H

#include <sys/queue.h>
#include "frame.h"

#define FISH_NAME_MAX_SIZE 30
#define FISH_PATH_SIZE 20

typedef struct fish
{
    char *name;
    frame *frame;
    int is_started;
    int position;
    frame *path[FISH_PATH_SIZE];
    STAILQ_ENTRY(fish)
    next;
} fish;

fish *fish__create(char *name, frame *frame);
void fish__free(fish *fish);
void fish__create_path(fish *f, frame *viewer);
#endif //FISH_H
