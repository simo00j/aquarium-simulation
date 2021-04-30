#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "control_server.h"

int server_connected = 0;

void control_server__connect() {
    server_connected = 1;
}

void control_server__disconnect() {
    server_connected = 0;
}

int control_server__is_connected() {
    return server_connected;
}