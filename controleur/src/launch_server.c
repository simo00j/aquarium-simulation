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
#include "command.h"
#include "control_client.h"
#include "control_server.h"

#define MAX_CLIENTS 50

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
    while (control_client__is_connected(newsockfd) && control_server__is_connected()) {
        bzero(buffer, 256);
        
        n = read(newsockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");

        //printf("Here is the message by socket %d: %s\n", newsockfd, buffer);
        

        message__read(buffer, newsockfd, answer_buffer);
        len_answer = strlen(answer_buffer);
        
        signal(SIGPIPE, SIG_IGN); // voir avec sigaction
        n = write(newsockfd, answer_buffer, len_answer);

        if (n < 0) {
            //printf("\n\nSocket %d left\n\n Commmand: ", newsockfd);
            return (void*) 0;
        }
    }
    return (void*) 0;
}

void* server_interface(void* args) {
    
    char buffer[256];
    char answer_buffer[256];
    (void) args;
    
    while(control_server__is_connected()){
        printf("Commande: ");
        bzero(buffer, 256);
        fgets(buffer, 255, stdin);
        
        command__read(buffer, answer_buffer);

        printf("%s\n", answer_buffer);
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

    control_server__connect();
    pthread_create(&thread_server, NULL, server_interface, NULL);
    
    
    while(control_server__is_connected()) {
        //voir select..
        newsockfd = accept(sockfd,
                        (struct sockaddr *)&cli_addr,
                        (socklen_t *)&clilen);

        if (newsockfd < 0) 
            error("ERROR on accept");

        control_client__connect(newsockfd);

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