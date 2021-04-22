#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "launch_server.h"
#include "config.h"

int main(void){

    int portno = config__get_port();
    int timeout = config__get_timeout();

    launch_server(portno, timeout);

    return 0;
}