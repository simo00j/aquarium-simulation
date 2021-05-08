#ifndef FRAME_H
#define FRAME_H

typedef struct frame
{
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;

} frame;

frame *frame__from_str(const char *string);
char *frame__to_str(const frame *frame);
int frame__includes_snippet(const frame *viewer, const frame *snippet);
void frame__move_randomly_inside(frame *snippet, const frame *viewer);
frame *frame__get_absolute(const frame *snippet, const frame *viewer);
frame *frame__get_relative(const frame *snippet, const frame *viewer);

#endif //FRAME_H
