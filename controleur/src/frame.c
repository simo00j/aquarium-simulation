#include <stdio.h>
#include <stdlib.h>
#include "frame.h"
#include "debug.h"

#define MAX_STR_FRAME_SIZE 30

/**
 * creates a frame from a string of form XxY+W+H
 * @param string : a string of form  XxY+W+H
 * @return a pointer to a frame, must be deallocated
 */
frame *frame__from_str(const char *string)
{
    frame *f = malloc(sizeof(frame));
    sscanf(string, "%dx%d+%d+%d", &f->x, &f->y, &f->width, &f->height);
    return f;
}

/**
 * transforms a frame into a string of form XxY,WxH
 * @param frame : a pointer to a frame
 * @return a pointer to a string of form XxY,WxH, must be deallocated
 */
char *frame__to_str(const frame *frame)
{
    char *str = malloc(sizeof(MAX_STR_FRAME_SIZE));
    snprintf(str, MAX_STR_FRAME_SIZE, "%dx%d,%dx%d", frame->x, frame->y, frame->width, frame->height);
    return str;
}

/**
 * checks if a frame 'viewer' contains another frame 'snippet'
 * @param viewer : a frame representing the viewer or aquarium
 * @param snippet : a frame representing a fish
 * @return 1 if viewer contains snippet and 0 if not
 */
int frame__includes_snippet(const frame *viewer, const frame *snippet)
{
    return snippet->x + snippet->width >= viewer->x &&
           snippet->y + snippet->height >= viewer->y &&
           snippet->x  <= viewer->x + viewer->width &&
           snippet->y  <= viewer->y + viewer->height;
}

void frame__move_randomly_inside(frame *snippet, const frame *viewer){
    (void)viewer;
    snippet->x = snippet->x - 40;
    //snippet->y = snippet->y + 5;
    DEBUG_OUT("generated position is : %s\n", frame__to_str(snippet));
}

frame *frame__get_absolute(const frame *snippet, const frame *viewer)
{
    frame *f = malloc(sizeof(frame));
    f->x = snippet->x * viewer->width / 100 + viewer->x;
    f->y = snippet->y * viewer->width / 100 + viewer->y;
    f->width = snippet->width * viewer->width / 100;
    f->height = snippet->height * viewer->height / 100;
    return f;
}
frame *frame__get_relative(const frame *snippet, const frame *viewer)
{
    frame *f = malloc(sizeof(frame));
    f->x = (snippet->x - viewer->x) * 100 / viewer->width;
    f->y = (snippet->y - viewer->y) * 100 / viewer->width;
    f->width = snippet->width * 100 / viewer->width;
    f->height = snippet->height * 100 / viewer->height;
    return f;
}