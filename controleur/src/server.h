#ifndef SERVER_H
#define SERVER_H

#include "utils.h"

typedef struct server {
    int port;
    int timeout;
    int fish_update_interval;
    status status;
    aquarium *aquarium;
    STAILQ_HEAD(, connection)
            connections_list;

}server;

int server__launch(server *server);
void *server__interface(void *args);

#endif //SERVER_H
