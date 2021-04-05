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


#include "launch_server.h"
#include "message.h"
#include "control.h"

#define MAX_CLIENTS 50

int server_connected = 0;

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
    char answer_buffer[256];
    while (control__is_connected(newsockfd) && server_connected) {
        bzero(buffer, 256);
        
        n = read(newsockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");

        //printf("Here is the message by thread %d: %s\n", newsockfd, buffer);
        

        message__processing(buffer, newsockfd, answer_buffer);
        len_answer = strlen(answer_buffer);
        
        signal(SIGPIPE, SIG_IGN); // voir avec sigaction
        n = write(newsockfd, answer_buffer, len_answer);

        if (n < 0) {
            //printf("\n\nThread %d left\n\n Commmand: ", newsockfd);
            return (void*) 0;
        }
    }
    return (void*) 0;
}

void* server_interface(void* args) {
    
    char buffer[256];
    (void) args;
    
    while(server_connected){
        printf("\nCommand: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        
        if(!strcmp(buffer, "close server\n")) {
            server_connected = 0;
            printf("Server disconnected\n");}
        else printf("Not a valid command\n ");
    }
    return (void*) 0;
}

int launch_server(int portno)
{
    int sockfd, newsockfd, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    thread_args_t* thread_args;
    pthread_t thread[MAX_CLIENTS];
    pthread_t thread_server;
    int nb_client = 0;
        
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

    server_connected = 1;
    pthread_create(&thread_server, NULL, server_interface, NULL);
    
    
    while(server_connected) {
        //voir select..
        newsockfd = accept(sockfd,
                        (struct sockaddr *)&cli_addr,
                        (socklen_t *)&clilen);

        if (newsockfd < 0) 
            error("ERROR on accept");

        control__connect(newsockfd);

        thread_args = malloc(sizeof(thread_args_t));
        thread_args->buffer = buffer;
        thread_args->newsockfd = newsockfd;

        pthread_create(&thread[nb_client], NULL, talk, thread_args);
        nb_client++;
    }

    pthread_join(thread_server, NULL);
    printf("join server done\n");
    for (int i = 0; i < nb_client; i++) {
        pthread_join(thread[i], NULL);
    }
    printf("join clients done\n");

    return 0;

}