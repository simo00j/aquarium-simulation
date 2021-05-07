#include <string.h>
#include <stdlib.h>
#include "view.h"

view *view__create(char *name, frame *frame)
{
    view *v = malloc(sizeof(view));
    v->name= (char*)malloc(sizeof(char) *30);
    strcpy(v->name, name);
    v->frame = frame;
    v->taken = 0;
    return v;
}

void view__free(view *view)
{
    free(view->name);
    free(view);
}