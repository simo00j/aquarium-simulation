#ifndef __DEBUG__H__
#define __DEBUG__H__

#define DEBUG 1
#if DEBUG
#define DEBUG_OUT(...)                         \
    do                                         \
    {                                          \
        fprintf(stderr, "DEBUG: "__VA_ARGS__); \
    } while (0)
#else
#define DEBUG_OUT(...)
#endif //DEBUG
#endif //__DEBUG__H__
