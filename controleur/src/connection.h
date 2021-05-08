#ifndef CONNECTION_H
#define CONNECTION_H

#include <sys/queue.h>
#include <pthread.h>
#include "view.h"
#include "utils.h"

#define BUFFER_MAX_SIZE 256

typedef struct connection
{
    int socket_fd;
    char *command_buffer;
    char *answer_buffer;
    view *associated_view;
    status status;
    int timeout;
    pthread_t thread;
    STAILQ_ENTRY(connection)
    next;
} connection;

void *connection__start(void *c);
void connection__end(int socket_fd);
void connection__free(connection * c);

#endif //CONNECTION_H
