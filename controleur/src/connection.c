#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>
#include "connection.h"
#include "control_client.h"
#include "control_server.h"
#include "utils.h"
#include "command.h"

extern aquarium *aq;

void *connection__start(void *c)
{
    connection *conn = (connection *)c;
    char *command_buffer = conn->command_buffer;
    int socket_fd = conn->socket_fd;
    int timeout = conn->timeout;
    conn->status = CONNECTED;
    int n, len_answer;
    char answer_buffer[BUFFER_MAX_SIZE];

    fd_set readfds;
    struct timeval time_out;
    FD_ZERO(&readfds);
    FD_SET(socket_fd, &readfds);
    time_out.tv_sec = 5;
    time_out.tv_usec = 0;

    while (control_client__is_connected(socket_fd) && control_server__is_connected())
    {
        time_out.tv_sec = timeout;
        time_out.tv_usec = 0;
        int a = select(FD_SETSIZE, &readfds, NULL, NULL, &time_out);
        if (a == 0)
        {
            control_client__disconnect(socket_fd);
            break;
        }

        bzero(command_buffer, BUFFER_MAX_SIZE);
        bzero(answer_buffer, BUFFER_MAX_SIZE);

        n = read(socket_fd, command_buffer, BUFFER_MAX_SIZE - 1);
        if (n < 0)
            error("ERROR reading from socket");

        command__from_client(command_buffer, answer_buffer, conn, aq);
        len_answer = strlen(answer_buffer);

        signal(SIGPIPE, SIG_IGN); // voir avec sigaction
        n = write(socket_fd, answer_buffer, len_answer);
        if (n < 0)
        {
            return (void *)0;
        }
    }

    return (void *)0;
}

void *connection__end(int socket_fd)
{
    close(socket_fd);
    return NULL;
}
