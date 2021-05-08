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
char *frame__to_str(frame *frame);
int frame__includes_snippet(const struct frame *position, const struct frame *snippet);
void frame__move_randomly(frame *frame);
frame *frame__get_absolute(frame *snippet, frame *viewer);
frame *frame__get_relative(frame *snippet, frame *viewer);

#endif //FRAME_H
