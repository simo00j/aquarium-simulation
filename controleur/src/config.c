#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "utils.h"

#define BUFFER_SIZE 100
#define CONFIG_PATH "controller.cfg"

int port = -1;
int timeout_value = -1;
int fish_update = -1;
int parsed = 0;

int get_config_value(char *tokens[])
{
    if (tokens[0] != NULL && tokens[1] != NULL)
        return atoi(tokens[1]);
    return -1;
}

void config__parser(FILE *config_file)
{
    char buffer[BUFFER_SIZE];
    char *tokens[10];
    int config_value;
    parsed = 1;

    while (!feof(config_file))
    {
        fgets(buffer, BUFFER_SIZE, config_file);
        util__parser(tokens, buffer, " = ");
        config_value = get_config_value(tokens);
        if (config_value != -1)
        {
            if (!strcmp(tokens[0], "controller-port"))
                port = config_value;
            
            else if (!strcmp(tokens[0], "display-timeout-value"))
                timeout_value = config_value;

            else if (!strcmp(tokens[0], "fish-update-interval"))
                fish_update = config_value;
        }
    }
}

void init_config()
{
    if (!parsed)
    {
        FILE *file;
        file = fopen(CONFIG_PATH, "r");
        if (file != NULL)
        {
            config__parser(file);
            fclose(file);
        }
        else
            error("Impossible d'ouvrir le fichier de configuration ( contoleur/controller.cfg )\n");
    }
}

int config__get_port()
{
    init_config();
    if (port == -1)
    {
        error("Numero de port requis dans le fichier de configuration ( contoleur/controller.cfg )\
        \nUsage\n \
        controller-port = <numero de port> \n \
        display-timeout-value = <duree (s)>\n \
        fish-update-interval =  <duree (s)>\n");
    }
    return port;
}

int config__get_timeout()
{
    init_config();
    if (timeout_value == -1)
    {
        error("Timeout requis dans le fichier de configuration ( contoleur/controller.cfg )\
        \nUsage\n \
        controller-port = <numero de port> \n \
        display-timeout-value = <duree (s)>\n \
        fish-update-interval =  <duree (s)>\n");
    }
    return timeout_value;
}

int config__get_fish_interval()
{
    init_config();
    if (fish_update == -1)
    {
        error("Fish update interval requis dans le fichier de configuration ( contoleur/controller.cfg )\
        \nUsage\n \
        controller-port = <numero de port> \n \
        display-timeout-value = <duree (s)>\n \
        fish-update-interval =  <duree (s)>\n");   
    }
    return fish_update;
}
