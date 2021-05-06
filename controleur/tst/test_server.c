#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <netdb.h>

#include "fake_client.h"

int main(void) {

    struct hostent *server = gethostbyname("localhost");
    int portno = 45321;

    launch_fake_client(portno, server);

    return 0;
}