#ifndef __CONNECTION__H__
#define __CONNECTION__H__

#include "view.h"

#define MAX_CONNECTIONS 50
#define BUFFER_MAX_SIZE 256

typedef enum status
{
    CONNECTED,
    PAUSED,
    DISCONNECTED,
} status;

typedef struct connection
{
    int socket_fd;
    char *command_buffer;
    char *answer_buffer;
    view *associated_view;
    status status;
    int timeout;
} connection;

void *connection__start(void *c);
void *connection__end(int socket_fd);

#endif //__CONNECTION__H__
