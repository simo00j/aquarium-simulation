#include <stdio.h>
#include <stdlib.h>
#include "frame.h"

#define MAX_STR_FRAME_SIZE 30

frame *frame__from_str(const char *string)
{
    frame *f = malloc(sizeof(frame));
    sscanf(string, "%dx%d+%d+%d", &f->x, &f->y, &f->width, &f->height);
    return f;
}

char *frame__to_str(frame *frame)
{
    char *str = malloc(sizeof(MAX_STR_FRAME_SIZE));
    snprintf(str, MAX_STR_FRAME_SIZE, "%dx%d,%dx%d", frame->x, frame->y, frame->width, frame->height);
    return str;
}

int frame__includes_snippet(const struct frame *frame, const struct frame *snippet)
{
    return snippet->x >= frame->x && snippet->y >= frame->y &&
           snippet->x + snippet->height <= frame->x + frame->height &&
           snippet->y + snippet->width <= frame->y + frame->width;
}

void frame__move_randomly(frame *frame){
    int index[] = {-1, 1};
    frame->x += index[rand() & 1] * rand()%50;
    frame->y += index[rand() & 1] * rand()%50;
}

frame *frame__get_absolute(frame *snippet, frame *viewer)
{
    frame *f = malloc(sizeof(frame));
    f->x = snippet->x + viewer->x;
    f->y = snippet->y + viewer->y;
    f->width = snippet->width * viewer->width / 100;
    f->height = snippet->height * viewer->height / 100;
    return f;
}
frame *frame__get_relative(frame *snippet, frame *viewer)
{
    frame *f = malloc(sizeof(frame));
    f->x = snippet->x - viewer->x;
    f->y = snippet->y - viewer->y;
    f->width = snippet->width * 100 / viewer->width;
    f->height = snippet->height * 100 / viewer->height;
    return f;
}