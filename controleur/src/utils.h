#ifndef UTILS_H
#define UTILS_H

typedef enum status
{
    CONNECTED,
    DISCONNECTED,
} status;

void exit_if(int cond, char *err);
void error(char *msg);
void util__parser(char *parsed_msg[], char *msg, char *sep);
int util__count_tokens(char *message[]);

#endif //UTILS_H