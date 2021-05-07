#ifndef FISH_H
#define FISH_H

#include <sys/queue.h>
#include "frame.h"

#define FISH_NAME_MAX_SIZE 30

typedef struct fish
{
    char *name;
    frame *frame;
    int is_started;
    STAILQ_ENTRY(fish)
    next;
} fish;

fish *fish__create(char *name, frame *frame);
void fish__free(fish *fish);

#endif //FISH_H
