#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include "connection.h"
#include "utils.h"
#include "command.h"
#include "server.h"

extern server *controller;

void *connection__start(void *c)
{
    connection *conn = (connection *)c;
    char answer_buffer[BUFFER_MAX_SIZE];
    conn->answer_buffer = answer_buffer;
    conn->associated_view = NULL;

    fd_set read_fds;
    struct timeval time_out;
    FD_ZERO(&read_fds);
    FD_SET(conn->socket_fd, &read_fds);
    time_out.tv_sec = 5;
    time_out.tv_usec = 0;

    while (conn->status == CONNECTED && controller->status == CONNECTED)
    {
        time_out.tv_sec = conn->timeout;
        time_out.tv_usec = 0;
        int a = select(FD_SETSIZE, &read_fds, NULL, NULL, &time_out);
        if (a == 0)
        {
            conn->status = DISCONNECTED;
            break;
        }

        bzero(conn->command_buffer, BUFFER_MAX_SIZE);
        bzero(conn->answer_buffer, BUFFER_MAX_SIZE);

        ssize_t err = read(conn->socket_fd, conn->command_buffer, BUFFER_MAX_SIZE - 1);
        exit_if(err < 0, "error on read()");
        command__from_client(conn, controller->aquarium);
        signal(SIGPIPE, connection__end);
        err = write(conn->socket_fd, conn->answer_buffer, strlen(conn->answer_buffer));
        exit_if(err < 0, "error on write()");
    }

    return (void *)0;
}

void connection__end(int socket_fd)
{
    close(socket_fd);
}
