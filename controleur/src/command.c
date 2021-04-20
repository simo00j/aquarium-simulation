#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "message.h"
#include "control_server.h"

#define CMD_SIZE 128

typedef enum command_type{
    CLOSE,
    LOAD,
    SHOW,
    ADD,
    DEL,
    SAVE,
    DEFAULT,
} command_type;


command_type command__get_type(char *cmd) {   
    if (!strcmp(cmd, "close")) 
        return CLOSE;
    if (!strcmp(cmd, "load")) 
        return LOAD;
    if (!strcmp(cmd, "show")) 
        return SHOW;
    if (!strcmp(cmd, "add")) 
        return ADD;
    if (!strcmp(cmd, "del")) 
        return DEL;
    if (!strcmp(cmd, "save")) 
        return SAVE;
    else return DEFAULT; 
}

void command__bad_args(char* cmd, char* answer_buffer) {
    sprintf(answer_buffer, "\n\tArguments non conformes\n\tUsage: \n\t\t> %s\n", cmd);
}

void command__default(char* answer_buffer) {
    sprintf(answer_buffer, "\n\tCommande introuvable \n\tDisponibles: \n\t\t> close \n\t\t> load \n\t\t> show \n\t\t> add \n\t\t> del \n\t\t> save\n");
}

void command__close_server(char* answer_buffer) {
    control_server__disconnect();
    sprintf(answer_buffer, "\n\tDéconnexion du serveur\n");
}

void command__load(char* answer_buffer) {
    sprintf(answer_buffer, "\nCommande existante non implémentée\n");
}

void command__show(char* answer_buffer) {
    sprintf(answer_buffer, "\nCommande existante non implémentée\n");
}

void command__add(char* answer_buffer) {
    sprintf(answer_buffer, "\nCommande existante non implémentée\n");
}

void command__del(char* answer_buffer) {
    sprintf(answer_buffer, "\nCommande existante non implémentée\n");
}

void command__save(char* answer_buffer) {
    sprintf(answer_buffer, "\nCommande existante non implémentée\n");
}

void command__read(char *cmd, char* answer_buffer) {
    char* command[CMD_SIZE];
    message__parser(command, cmd);
    command_type type = command__get_type(command[0]);
    int nb_args = count_args(command);

    switch (type) {
        case CLOSE:
        if (nb_args == 1 
        && !strcmp(command[1], "server"))
            command__close_server(answer_buffer);
        else command__bad_args("close server", answer_buffer);
        break;

        case LOAD:
        command__load(answer_buffer);
        break;

        case SHOW:
        command__show(answer_buffer);
        break;

        case ADD:
        command__add(answer_buffer);
        break;

        case DEL:
        command__del(answer_buffer);
        break;

        case SAVE:
        command__save(answer_buffer);
        break;

        default:
        command__default(answer_buffer);
        break;
    }
}


/*
int main(){
    char str[] ="close server\n";
    char buf[256];
    command__read(str, buf);
    printf("Returned: %s", buf);
}
*/