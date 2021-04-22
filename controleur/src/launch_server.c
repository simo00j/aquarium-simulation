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
#include "util.h"

#define MAX_CLIENTS 50
#define BUFFER_SIZE 256


typedef struct thread_args_t {
    char* buffer;
    int sockfd;
    int timeout;
} thread_args_t;

void* talk(void* args) {
    thread_args_t *arg = (thread_args_t*) args;
    char* buffer = arg->buffer;
    int sockfd = arg->sockfd;
    int timeout = arg->timeout;
    int n, len_answer;
    char answer_buffer[BUFFER_SIZE];

    fd_set readfds;
    struct timeval time_out;
    FD_ZERO(&readfds);
    FD_SET(sockfd,&readfds);
    time_out.tv_sec = 5;    // 10 seconds
    time_out.tv_usec = 0;    // 0 milliseconds

    while (control_client__is_connected(sockfd) && control_server__is_connected()) { 
        time_out.tv_sec = timeout;    // 100 seconds 
        time_out.tv_usec = 0;
        int a = select(FD_SETSIZE,&readfds,NULL,NULL,&time_out);
        //if (a == -1) error("Error select");
        if (a == 0) {
            control_client__disconnect(sockfd);
            break;
        }

        bzero(buffer, BUFFER_SIZE);
        bzero(answer_buffer, BUFFER_SIZE);

        n = read(sockfd, buffer, BUFFER_SIZE - 1);
        if (n < 0)
            error("ERROR reading from socket");

        message__read(buffer, sockfd, answer_buffer);
        len_answer = strlen(answer_buffer);
        
        signal(SIGPIPE, SIG_IGN); // voir avec sigaction
        n = write(sockfd, answer_buffer, len_answer);
        if (n < 0) {
            return (void*) 0;
        }
    }
    //close(sockfd);

    return (void*) 0;
}

void* server_interface(void* args) {
    
    char buffer[BUFFER_SIZE];
    char answer_buffer[BUFFER_SIZE];
    (void) args;
    
    while(control_server__is_connected()){
        printf("Commande: ");
        bzero(buffer, BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE - 1, stdin);
        
        command__read(buffer, answer_buffer);

        printf("%s\n", answer_buffer);
    }
    return (void*) 0;
}

int launch_server(int portno, int timeout) 
{
    int sockfd, newsockfd, clilen;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    thread_args_t* thread_args;
    pthread_t thread[MAX_CLIENTS];
    pthread_t thread_server;
    int nb_client = 0;
    /*    
    fd_set readfds;
    struct timeval time_out;
    FD_ZERO(&readfds);
  //    FD_ZERO(&writefds);
        

    time_out.tv_sec = 10;    // 10 seconds
    time_out.tv_usec = 0;    // 0 milliseconds
    */
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
    //FD_SET(sockfd,&readfds);
    //int i = 0;
    while(control_server__is_connected()) {
        /*
        int a = select(FD_SETSIZE,&readfds,NULL,NULL,&time_out);
        //if (a == -1) error("Error select");
        if (a == 0) {
            
            printf("%d\n", i++);
            if (!control_server__is_connected())
                break;
            else {
                time_out.tv_sec = 10;    // 10 seconds
                time_out.tv_usec = 0; 
                continue;
            }
        }
       */
        newsockfd = accept(sockfd,
                        (struct sockaddr *)&cli_addr,
                        (socklen_t *)&clilen);

        if (newsockfd < 0) 
            error("ERROR on accept");

        control_client__connect(newsockfd);
        
        thread_args = malloc(sizeof(thread_args_t));
        thread_args->buffer = buffer;
        thread_args->sockfd = newsockfd;
        thread_args->timeout = timeout;

        pthread_create(&thread[nb_client], NULL, talk, thread_args);
        nb_client++;
    }

    pthread_join(thread_server, NULL);
    if(nb_client > 0) {
        printf("\tFermeture des clients\n\n");
    }
    for (int i = 0; i < nb_client; i++) {
        pthread_join(thread[i], NULL);
        printf("\t\tClients fermés: %d/%d\n", i+1, nb_client);
    }
    printf("\n\tDéconnexion terminée avec succès\n\n");

    return 0;

}