#ifndef __CLIENT_PARSER__H__
#define __CLIENT_PARSER__H__

#include "connection.h"
#include "aquarium.h"

#define COMMAND__MAX_SIZE 128

typedef enum client_command_type
{
    PING,
    STATUS,
    ADD_FISH,
    DEL_FISH,
    START_FISH,
    GET_FISHES,
    GET_FISHES_CONTINUOUSLY,
    LS,
    LOG_OUT,
} client_command_type;

typedef enum server_command_type
{
    LOAD,
    SHOW,
    ADD_VIEW,
    DEL_VIEW,
    SAVE,
} server_command_type;

typedef struct server_command
{
    char **args;
    server_command_type type;
} server_command;

typedef struct client_command
{
    char *args;
    client_command_type type;
} client_command;

void command__from_server(char *cmd, char *answer);
void command__from_client(char *cmd, char *answer_buffer, connection *c, aquarium *aq);
void *connection__ls(void *connection);

#endif //__CLIENT_PARSER__H__
