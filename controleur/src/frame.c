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
