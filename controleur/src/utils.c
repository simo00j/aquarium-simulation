#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void error(char *message)
{
    perror(message);
    exit(1);
}

void exit_if(int cond, char *err)
{
    if (cond)
    {
        error(err);
    }
}

void util__parser(char *parsed_message[], char *message, char *separator)
{
    message[strlen(message) - 1] = ' ';
    char *token = strtok(message, separator);
    if (token != NULL)
    {
        parsed_message[0] = token;
        int args = 1;
        while (token != NULL)
        {
            token = strtok(NULL, separator);
            parsed_message[args++] = token;
        }
        parsed_message[args] = NULL;
    }
}

void myParser(char *parsed_message[], char *message, char *separator)
{
    char *token;
    token = strtok(message, separator);
    if (token != NULL)
    {
        parsed_message[0] = token;
        int args = 1;
        while (token != NULL)
        {
            token = strtok(NULL, separator);
            parsed_message[args++] = token;
        }
        parsed_message[args] = NULL;
    }
}

int util__count_tokens(char *message[])
{
    int i = 0;
    while (message[i] != NULL)
    {
        i++;
    }
    return i;
}