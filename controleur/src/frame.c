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

char *frame__to_str(const frame *frame)
{
    char *str = malloc(sizeof(MAX_STR_FRAME_SIZE));
    snprintf(str, MAX_STR_FRAME_SIZE, "%dx%d,%dx%d", frame->x, frame->y, frame->width, frame->height);
    return str;
}

int frame__includes_snippet(const frame *viewer, const frame *snippet)
{
    return snippet->x + snippet->width >= viewer->x 
    && snippet->y + snippet->height >= viewer->y 
    && snippet->x  <= viewer->x + viewer->width 
    && snippet->y  <= viewer->y + viewer->height;
}

void frame__move_randomly_inside(frame *snippet, const frame *viewer){
    snippet->x = rand() % viewer->width;
    snippet->y = rand() % viewer->height;
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

//A ENLEVER
/*
int main() {
    frame* view = frame__from_str("500x500+500+500");
    frame* fish1 = frame__from_str("501x501+10+10");
    frame* fish2 = frame__from_str("499x499+10+10");
    frame* fish3 = frame__from_str("999x999+10+10");
    frame* fish4 = frame__from_str("489x502+10+10");
    frame* fish5 = frame__from_str("1001x499+10+10");

    frame* fishes[5] = {fish1, fish2, fish3, fish4, fish5};
    for (int i = 0; i < 5; i++) {
        printf("include fish %d: %s\n", i + 1, frame__includes_snippet(view, fishes[i]) ? "oui":"non" );

        frame *relative_fish = frame__get_relative(fishes[i], view);
        printf("relative position: %s\n\n", frame__to_str(relative_fish));
        free(fishes[i]);
        free(relative_fish);
    }
    free(view);
}
*/