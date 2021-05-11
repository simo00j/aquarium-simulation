#include <stdio.h>
#include <stdlib.h>
#include "frame.h"
#include "debug.h"

#define MAX_STR_FRAME_SIZE 30

frame *frame__from_str(const char *string)
{
    frame *f = malloc(sizeof(frame));
    sscanf(string, "%dx%d+%d+%d", &f->x, &f->y, &f->width, &f->height);
    return f;
}

char *frame__to_str(const frame *frame)
{
    char *str = malloc(sizeof(MAX_STR_FRAME_SIZE));
    snprintf(str, MAX_STR_FRAME_SIZE, "%dx%d,%dx%d", frame->x, frame->y, frame->width, frame->height);
    return str;
}

int frame__includes_snippet(const frame *viewer, const frame *snippet)
{
    return snippet->x + snippet->width >= viewer->x && snippet->y + snippet->height >= viewer->y && snippet->x  <= viewer->x + viewer->width && snippet->y  <= viewer->y + viewer->height;
}

void frame__move_randomly_inside(frame *snippet, const frame *viewer){
    snippet->x = (snippet->x + 10) % viewer->width;
    DEBUG_OUT("generated position is : %s", frame__to_str(snippet));
    //snippet->y = rand() % viewer->height;
}

frame *frame__get_absolute(const frame *snippet, const frame *viewer)
{
    frame *f = malloc(sizeof(frame));
    f->x = snippet->x + viewer->x;
    f->y = snippet->y + viewer->y;
    f->width = snippet->width * viewer->width / 100;
    f->height = snippet->height * viewer->height / 100;
    return f;
}
frame *frame__get_relative(const frame *snippet, const frame *viewer)
{
    frame *f = malloc(sizeof(frame));
    f->x = snippet->x - viewer->x;
    f->y = snippet->y - viewer->y;
    f->width = snippet->width * 100 / viewer->width;
    f->height = snippet->height * 100 / viewer->height;
    return f;
}