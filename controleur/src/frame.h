#ifndef __POSITION__H__
#define __POSITION__H__

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

#endif //__POSITION__H__
