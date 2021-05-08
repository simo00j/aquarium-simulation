#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "command.h"
#include "aquarium.h"
#include "utils.h"
#include "server.h"
#include "config.h"

server *controller;

void *server__interface(void *args)
{

    char buffer[BUFFER_MAX_SIZE];
    char answer_buffer[BUFFER_MAX_SIZE];
    (void)args;

    while (controller->status == CONNECTED)
    {
        printf("$ ");
        bzero(buffer, BUFFER_MAX_SIZE);
        bzero(answer_buffer, BUFFER_MAX_SIZE);
        fgets(buffer, BUFFER_MAX_SIZE - 1, stdin);
        command__from_server(buffer, answer_buffer,controller->aquarium);
        printf("%s\n", answer_buffer);
    }
    return (void *)0;
}

void *update_randomly(void *args)
{
    (void)args;
    while (controller->status == CONNECTED)
    {
        aquarium__update_fish_randomly(controller->aquarium);
        sleep(1);
    }
    return (void *)0;
}

int server__launch(server *server)
{
    int socket_fd, clilen;
    char buffer[BUFFER_MAX_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    connection *conn;
    pthread_t thread_server, thread_update;
    controller->aquarium = aquarium__empty();
    STAILQ_INIT(&(controller->connections_list));
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    exit_if(socket_fd < 0, "error while creating socket");
    exit_if(setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0, "setsockopt(SO_REUSEADDR) failed");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(server->port);

    exit_if(bind(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0, "ERROR on bind()");

    listen(socket_fd, 5);
    clilen = sizeof(cli_addr);

    server->status = CONNECTED;
    pthread_create(&thread_server, NULL, server__interface, NULL);
    pthread_create(&thread_update, NULL, update_randomly, NULL);
    while (server->status == CONNECTED)
    {
        conn = malloc(sizeof(connection));
        conn->command_buffer = buffer;
        conn->socket_fd = accept(socket_fd, (struct sockaddr *)&cli_addr, (socklen_t *)&clilen);
        exit_if(conn->socket_fd < 0, "error on accept()");
        conn->timeout = server->timeout;
        conn->status = CONNECTED;
        STAILQ_INSERT_HEAD(&(controller->connections_list), conn, next);
        pthread_create(&(conn->thread), NULL, connection__start, conn);
    }
    pthread_join(thread_server, NULL);
    pthread_join(thread_update, NULL);
    connection *c;
    STAILQ_FOREACH(c, &(controller->connections_list), next)
    {
        pthread_join(c->thread, NULL);
    }
    return 0;
}

int main(void)
{
    controller = malloc(sizeof(server));
    controller->port = config__get_port();
    controller->timeout = config__get_timeout();
    controller->fish_update_interval = config__get_fish_interval();
    server__launch(controller);
    return 0;
}