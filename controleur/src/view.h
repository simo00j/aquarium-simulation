#ifndef __VIEW__H__
#define __VIEW__H__

#include <sys/queue.h>
#include "frame.h"

#define VIEW_NAME_MAX_SIZE 5

typedef struct view
{
    char *name;
    frame *frame;
    int taken;
    STAILQ_ENTRY(view)
    next;
} view;

view *view__create(char *name, frame *frame);
void view__free(view *view);

#endif //__VIEW__H__