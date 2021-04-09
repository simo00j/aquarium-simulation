#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "launch_server.h"

int main(int argc, char *argv[]){

    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    int portno = atoi(argv[1]);

    launch_server(portno);

    return 0;
}