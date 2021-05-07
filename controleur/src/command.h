#ifndef CLIENT_PARSER_H
#define CLIENT_PARSER_H

#include "connection.h"
#include "aquarium.h"

#define COMMAND__MAX_SIZE 128

void command__from_server(char *cmd, char *answer, aquarium *aq);
void command__from_client(connection *c, aquarium *aq);
void *connection__ls(void *connection);

#endif //CLIENT_PARSER_H
