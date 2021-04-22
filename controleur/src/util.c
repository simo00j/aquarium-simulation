#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"


void error(char *msg)
{
    perror(msg);
    exit(1);
}

void util__parser(char* parsed_msg[], char* msg, char* sep) {
    size_t l = strlen(msg);
    msg[l-1] = ' ';
    char* token;
    token = strtok(msg, sep); 
    if(token != NULL) {
        parsed_msg[0] = token;
        int args = 1;
        while( token != NULL ) {
            token = strtok(NULL, sep);
            parsed_msg[args++] = token;
        }
        parsed_msg[args] = NULL;
    }
}

int util__count_args(char* message[]) {
    int i = 1;
    while(message[i] != NULL) {
        i++;
    } 
    return i - 1;
}