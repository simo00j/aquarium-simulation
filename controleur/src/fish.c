#include <stdlib.h>
#include <string.h>
#include "fish.h"

fish *fish__create(char *name, frame *intial_frame)
{
    fish *f = malloc(sizeof(fish));
    f->is_started = 0;
    f->position = 0;
    f->name = malloc(sizeof(char) * FISH_NAME_MAX_SIZE);
    f->frame = intial_frame;
    strcpy(f->name, name);
    return f;
}

void fish__create_path(fish *f, frame *viewer)
{
    f->path[0] = f->frame;
    frame__move_randomly_inside(f->path[0], viewer);
    for (int i = 1; i < FISH_PATH_SIZE; ++i) {
        f->path[i] = malloc(sizeof(frame));
        f->path[i]->width = f->frame->width;
        f->path[i]->height = f->frame->height;
        f->path[i]->y = f->path[i-1]->y;
        f->path[i]->x = f->path[i-1]->x;
        frame__move_randomly_inside(f->path[i], viewer);
    }
}

void fish__free(fish *fish)
{
    free(fish->name);
    free(fish->frame);
    // free the path
    free(fish);
}
