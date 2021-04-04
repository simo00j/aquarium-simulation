#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "message.h"
#include "control.h"

#define MSG_SIZE 128
#define BUFFER_SIZE 256

typedef enum message_type{
    HELLO,
    GET_FISHES,
    LOG,
    PING,
    STATUS,
    DEFAULT,
} message_type;

char answer_buffer[BUFFER_SIZE]; //dangereux avec les thread, a voir si autre idée (ou au moins mettre des mutex)

message_type message__get_type(char *cmd) {   
    if (!strcmp(cmd, "hello")) 
        return HELLO;
    if (!strcmp(cmd, "getFishes")) 
        return GET_FISHES;
    if (!strcmp(cmd, "log")) 
        return LOG;
    if (!strcmp(cmd, "ping")) 
        return PING;
    if (!strcmp(cmd, "status")) 
        return STATUS;
    else return DEFAULT; 
}

void message__parser(char* parsed_msg[], char* msg) {
    size_t l = strlen(msg);
    msg[l-1] = ' ';
    char* token;
    token = strtok(msg, " "); 

    if(token != NULL) {
        parsed_msg[0] = token;
        int args = 1;
        while( token != NULL ) {
            token = strtok(NULL, " ");
            parsed_msg[args++] = token;
        }
        parsed_msg[args] = NULL;
    }
}

void message__hello_in_as_id(int aquarium_id, int id) {
    int new_aquarium_id = control__ask_id_hello_in_as(aquarium_id, id);
    if (new_aquarium_id > -1)
        sprintf(answer_buffer, "gretting %d\n", new_aquarium_id);
    else sprintf(answer_buffer, "no gretting\n");
}

void message__hello(int id) {
    int new_aquarium_id = control__ask_id_hello(id);
    if (new_aquarium_id > -1)
        sprintf(answer_buffer, "gretting %d\n", new_aquarium_id);
    else sprintf(answer_buffer, "no gretting\n");
}

void message__getFishes() {
    sprintf(answer_buffer, "list [PoissonRouge at 90x4,10x4,5] [PoissonClown at 20x80,12x6,5]\n");
}

void message__log_out(int id) {
    control__disconnect(id);
    sprintf(answer_buffer, "bye\n");
}

void message__ping(int ping) {
    sprintf(answer_buffer, "pong %d\n", ping);
}

void message__status() {
    sprintf(answer_buffer, "Connecté au controleur\n");
}

void message__default() {
    sprintf(answer_buffer, "Commande introuvable\n");
}

void message__bad_args(char* cmd) {
    sprintf(answer_buffer, "Arguments non conformes pour la commande %s\n", cmd);
}

int count_args(char* message[]) {
    int i = 1;
    while(message[i] != NULL) {
        i++;
    } 
    return i - 1;
}

void message__read(char *msg, int id) {
    char* message[MSG_SIZE];
    message__parser(message, msg);
    message_type type = message__get_type(message[0]);
    int nb_args = count_args(message);

    switch (type) {
        case PING:
        if (nb_args == 1) 
            message__ping(atoi(message[1]));
        else message__bad_args("ping");
        break;

        case HELLO:
        if (nb_args == 3
        && !strcmp(message[1], "in")
        && !strcmp(message[2], "as"))
            message__hello_in_as_id(atoi(message[3]), id);
        else if (nb_args == 0) message__hello(id);
        else message__bad_args("hello");
        break;

        case GET_FISHES:
        if (nb_args == 0) message__getFishes();
        else message__bad_args("getFishes");
        break;

        case STATUS:
        if (nb_args == 0) message__status();
        else message__bad_args("status");
        break;

        case LOG:
        if (nb_args == 1 
        && !strcmp(message[1], "out"))
            message__log_out(id);
        else message__bad_args("log");
        break;

        default:
        message__default();
        break;
    }
}

char* message__processing(char* msg, int id) {
    message__read(msg, id);
    return answer_buffer;
}
/*
int main(){
    char str[] =" hello ";
    printf("Returned: %s",message__processing(str));
}
*/