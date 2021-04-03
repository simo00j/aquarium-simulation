#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <pthread.h>

#include "launch_server.h"
#include "message.h"
#include "control.h"

void error(char *msg)
{
    perror(msg);
    exit(1);
}

typedef struct thread_args_t {
    char* buffer;
    int newsockfd;
} thread_args_t;

void* talk(void* args) {
    thread_args_t *arg = (thread_args_t*) args;
    char* buffer = arg->buffer;
    int newsockfd = arg->newsockfd;
    int n, len_answer;
    char* answer;
    while (control__is_connected(newsockfd)) {
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");

        printf("Here is the message by %d: %s\n", newsockfd, buffer);

        answer = message__processing(buffer, newsockfd);
        len_answer = strlen(answer);
        
        n = write(newsockfd, answer, len_answer);

        if (n < 0)
            error("ERROR writing to socket");
    }
    return (void*) 0;
}

int launch_server(int portno)
{
    int sockfd, newsockfd, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    thread_args_t* thread_args;
    pthread_t thread;
        
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *)&serv_addr,
             sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while(1) {
        newsockfd = accept(sockfd,
                        (struct sockaddr *)&cli_addr,
                        (socklen_t *)&clilen);

        if (newsockfd < 0) 
            error("ERROR on accept");

        control__connect(newsockfd);

        thread_args = malloc(sizeof(thread_args_t));
        thread_args->buffer = buffer;
        thread_args->newsockfd = newsockfd;

        pthread_create(&thread, NULL, talk, thread_args);
    }

    return 0;

}