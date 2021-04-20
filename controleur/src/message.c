#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "message.h"
#include "control_client.h"

#define MSG_SIZE 128
#define BUFFER_SIZE 256

typedef enum message_type{
    HELLO,
    GET_FISHES,
    LOG,
    PING,
    STATUS,
    ADD_FISH,
    DEL_FISH,
    START_FISH,
    LS,
    GET_FISHES_CONTINUOUSLY,
    DEFAULT,
} message_type;

message_type message__get_type(char *cmd) {   
    if (!strcmp(cmd, "hello")) 
        return HELLO;
    if (!strcmp(cmd, "getFishes")) 
        return GET_FISHES;
    if (!strcmp(cmd, "log")) 
        return LOG;
    if (!strcmp(cmd, "ping")) 
        return PING;
    if (!strcmp(cmd, "addFish")) 
        return ADD_FISH;
    if (!strcmp(cmd, "delFish")) 
        return DEL_FISH;
    if (!strcmp(cmd, "startFish")) 
        return START_FISH;
    if (!strcmp(cmd, "ls")) 
        return LS;
    if (!strcmp(cmd, "getFishesContinuously")) 
        return GET_FISHES_CONTINUOUSLY;
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

void message__hello_in_as_id(int aquarium_id, int socketfd, char* answer_buffer) {
    int new_aquarium_id = control_client__set_aquarium_id_named(aquarium_id, socketfd);
    if (new_aquarium_id > -1)
        sprintf(answer_buffer, "gretting %d\n", new_aquarium_id);
    else sprintf(answer_buffer, "no gretting\n");
}

void message__hello(int socketfd, char* answer_buffer) {
    int new_aquarium_id = control_client__set_aquarium_id(socketfd);
    if (new_aquarium_id > -1)
        sprintf(answer_buffer, "gretting %d\n", new_aquarium_id);
    else sprintf(answer_buffer, "no gretting\n");
}

void message__getFishes(char* answer_buffer) {
    sprintf(answer_buffer, "list [PoissonRouge at 90x4,10x4,5] [PoissonClown at 20x80,12x6,5]\n");
}

void message__log_out(int socketfd, char* answer_buffer) {
    control_client__disconnect(socketfd);
    sprintf(answer_buffer, "bye\n");
}

void message__ping(int ping, char* answer_buffer) {
    sprintf(answer_buffer, "pong %d\n", ping);
}

void message__status(char* answer_buffer) {
    sprintf(answer_buffer, "Connecté au control_clienteur\n");
}

void message__add_fish(char* answer_buffer) {
    sprintf(answer_buffer, "Pas encore implémenté\n");
}

void message__del_fish(char* answer_buffer) {
    sprintf(answer_buffer, "Pas encore implémenté\n");
}

void message__start_fish(char* answer_buffer) {
    sprintf(answer_buffer, "Pas encore implémenté\n");
}

void message__ls(char* answer_buffer) {
    sprintf(answer_buffer, "Pas encore implémenté\n");
}

void message__get_fishes_continuously(char* answer_buffer) {
    sprintf(answer_buffer, "Pas encore implémenté\n");
}

void message__default(char* answer_buffer) {
    sprintf(answer_buffer, "Commande introuvable\n");
}

void message__bad_args(char* cmd, char* answer_buffer) {
    sprintf(answer_buffer, "Arguments non conformes pour la commande %s\n", cmd);
}

int count_args(char* message[]) {
    int i = 1;
    while(message[i] != NULL) {
        i++;
    } 
    return i - 1;
}

void message__read(char *msg, int socketfd, char* answer_buffer) {
    char* message[MSG_SIZE];
    message__parser(message, msg);
    message_type type = message__get_type(message[0]);
    int nb_args = count_args(message);

    switch (type) {
        case PING:
        if (nb_args == 1) 
            message__ping(atoi(message[1]), answer_buffer);
        else message__bad_args("ping", answer_buffer);
        break;

        case HELLO:
        if (nb_args == 3
        && !strcmp(message[1], "in")
        && !strcmp(message[2], "as"))
            message__hello_in_as_id(atoi(message[3]), socketfd, answer_buffer);
        else if (nb_args == 0) message__hello(socketfd, answer_buffer);
        else message__bad_args("hello", answer_buffer);
        break;

        case GET_FISHES:
        if (nb_args == 0) message__getFishes(answer_buffer);
        else message__bad_args("getFishes", answer_buffer);
        break;

        case STATUS:
        if (nb_args == 0) message__status(answer_buffer);
        else message__bad_args("status", answer_buffer);
        break;

        case LOG:
        if (nb_args == 1 
        && !strcmp(message[1], "out"))
            message__log_out(socketfd, answer_buffer);
        else message__bad_args("log", answer_buffer);
        break;

        case ADD_FISH:
        message__add_fish(answer_buffer);
        break;

        case DEL_FISH:
        message__del_fish(answer_buffer);
        break;

        case START_FISH:
        message__start_fish(answer_buffer);
        break;

        case LS:
        message__ls(answer_buffer);
        break;

        case GET_FISHES_CONTINUOUSLY:
        message__get_fishes_continuously(answer_buffer);
        break;

        default:
        message__default(answer_buffer);
        break;
    }
}


/*
int main(){
    char str[] ="hello\n";
    char buf[256];
    message__read(str, 0, buf);
    printf("Returned: %s",buf);
}
*/