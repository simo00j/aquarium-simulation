#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "util.h"
#include "control_server.h"
#include "aquarium.h"

#define CMD_SIZE 128
#define AQUA_DATA_PATH "data/"
static char path[64];


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

void command__load(char* aquarium, char* answer_buffer) {
    struct aquarium *aq;
    sprintf(path, "%s%s.txt", AQUA_DATA_PATH, aquarium);
    FILE *f = fopen(path, "r");
    if (!f) {
        sprintf(answer_buffer, "\n\tAquarium %s introuvable \n\tL'aquarium doit être enregistré dans le dossier data/ sous la forme: %s.txt\n", aquarium, aquarium);
        return; 
    }
    aq = loadDataFromFile(f);
    if(aq == NULL) 
            sprintf(answer_buffer, "\n\tChargement impossible\n");
    else sprintf(answer_buffer, "\n\tChargement de l'aquarium effectué (%d view disponible)\n", aq->views_number);
    fclose(f);
}

void command__show() {
    char buffer[CMD_SIZE];
    int aq = get_aquarium_data(buffer);
    if (aq == 0) {
        printf("\n\tAucun aquarium n'a été initialisé\n\tUn aquarium peut être initialisé grace à la commande:\n\t\tload aquarium<n>\n");
        return;
    }
    aquarium *a = get_aquarium();
    printf("%dx%d\n", a->size.width, a->size.height);
    for(int i = 0; i < a->views_number; i++){
        view *v = a->views[i];
        printf("%s %dx%d+%d+%d\n", v->name, v->size.width, v->size.height, v->position.x, v->position.y);
    }
}

void command__add(char** command) {
    
    int nb_args = util__count_args(command);
    if(nb_args == 3 && strcmp(command[1], "view") == 0){
        char name[3];
        strcpy(name, command[2]);
        char* command2[CMD_SIZE];
        myParser(command2, command[3], "+");
        size s;
        s.width = atoi(command2[1]);
        s.height = atoi(command2[2]);
        char* command3[CMD_SIZE];
        myParser(command3, command2[0], "x");
        position pos;
        pos.x = atoi(command3[0]);
        pos.y = atoi(command3[1]);
        aquarium *a = get_aquarium();
        int n = addView(name, pos, s, a);
        if(n)
            printf("view (name: %s, x: %d, y: %d, width: %d, height: %d) added", name, pos.x, pos.y, s.width, s.height);
        else
            printf("\nView can not be added\n");
    }
    else
        printf("\nView can not be added\n");
}

void command__del(char** command) {

    int nb_args = util__count_args(command);
    if(nb_args == 2 && strcmp(command[1], "view") == 0){
        aquarium *a = get_aquarium();
        int d = delView(command[2], a);
        if(d)
            printf("view %s deleted\n", command[2]);
        else
            printf("view %s does not exist\n", command[2]);

    }
    else
        printf("view %s can not be deleted\n", command[2]);
}

void command__save() {

    FILE *f = fopen(path, "w+");
    aquarium *a = get_aquarium();
    char s[40];
    sprintf(s, "%dx%d\n", a->size.width, a->size.height);
    fputs(s, f);
    for(int i = 0; i < a->views_number; i++){
        view *v = a->views[i];
        sprintf(s, "%s %dx%d+%d+%d\n", v->name, v->size.width, v->size.height, v->position.x, v->position.y);
        fputs(s, f);
    }
    
    fclose(f);
    printf("aquarium saved! (%d display views)", a->views_number);    
}

void command__read(char *cmd, char* answer_buffer) {
    char* command[CMD_SIZE];
    util__parser(command, cmd, " ");
    command_type type = command__get_type(command[0]);
    int nb_args = util__count_args(command);

    switch (type) {
        case CLOSE:
        if (nb_args == 1 
        && !strcmp(command[1], "server"))
            command__close_server(answer_buffer);
        else command__bad_args("close server", answer_buffer);
        break;

        case LOAD:
        if (nb_args == 1)
            command__load(command[1], answer_buffer);
        else command__bad_args("load aquarium<n>", answer_buffer);
        break;

        case SHOW:
        command__show();
        break;

        case ADD:
        command__add(command);
        break;

        case DEL:
        command__del(command);
        break;

        case SAVE:
        command__save();
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