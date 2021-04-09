#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <netdb.h>

#include "fake_client.h"

int main(int argc, char *argv[]) {

    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    struct hostent *server = gethostbyname(argv[1]);
    int portno = atoi(argv[2]);

    launch_fake_client(portno, server);

    return 0;
}