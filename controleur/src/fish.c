#include <stdlib.h>
#include <string.h>
#include "fish.h"

fish *fish__create(char *name, frame *intial_frame)
{
    fish *f = malloc(sizeof(fish));
    f->name = malloc(sizeof(char) * FISH_NAME_MAX_SIZE);
    strcpy(f->name, name);
    f->frame = intial_frame;
    f->is_started = 0;
    return f;
}
void fish__free(fish *fish)
{
    free(fish->name);
    free(fish->frame);
    free(fish);
}
