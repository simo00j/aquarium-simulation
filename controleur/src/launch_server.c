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
#include "command.h"
#include "aquarium.h"
#include "control_client.h"
#include "control_server.h"
#include "utils.h"

#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

aquarium *aq;

void *server_interface(void *args)
{

    char buffer[BUFFER_MAX_SIZE];
    char answer_buffer[BUFFER_MAX_SIZE];
    (void)args;

    while (control_server__is_connected())
    {
        printf("$ ");
        bzero(buffer, BUFFER_MAX_SIZE);
        bzero(answer_buffer, BUFFER_MAX_SIZE);
        fgets(buffer, BUFFER_MAX_SIZE - 1, stdin);

        command__from_server(buffer, answer_buffer);

        printf("%s\n" ANSI_COLOR_RESET, answer_buffer);
    }
    return (void *)0;
}

int launch_server(int portno, int timeout)
{
    int sockfd, newsockfd, clilen;
    char buffer[BUFFER_MAX_SIZE];
    struct sockaddr_in serv_addr, cli_addr;
    connection *conn;
    pthread_t thread[CONNECTIONS_MAX_NUMBER];
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
    FILE *f = fopen("data/aquarium1.txt", "r");
    aq = aquarium__load(f);
    fclose(f);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        error("setsockopt(SO_REUSEADDR) failed");

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
    while (control_server__is_connected())
    {
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

        conn = malloc(sizeof(connection));
        conn->command_buffer = buffer;
        conn->socket_fd = newsockfd;
        conn->timeout = timeout;

        pthread_create(&thread[nb_client], NULL, connection__start, conn);
        nb_client++;
    }

    pthread_join(thread_server, NULL);
    if (nb_client > 0)
    {
        printf("\tFermeture des clients\n\n");
    }
    for (int i = 0; i < nb_client; i++)
    {
        pthread_join(thread[i], NULL);
        printf("\t\tClients fermés: %d/%d\n", i + 1, nb_client);
    }
    printf("\n\tDéconnexion terminée avec succès\n\n");

    return 0;
}
