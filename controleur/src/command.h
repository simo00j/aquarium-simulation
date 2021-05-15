#ifndef COMMAND_H
#define COMMAND_H

#include "connection.h"
#include "aquarium.h"

#define COMMAND__MAX_SIZE 128

void command__from_server(char *cmd, char *answer, aquarium *aq);
void command__from_client(connection *c, aquarium *aq);
void *connection__get_fish_continuously(void *connection);

#endif //COMMAND_H
