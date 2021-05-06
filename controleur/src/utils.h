#ifndef __UTILS__H__
#define __UTILS__H__

void exit_if(int cond, char *err);
void error(char *msg);
void util__parser(char *parsed_msg[], char *msg, char *sep);
void myParser(char *parsed_msg[], char *msg, char *sep);
int util__count_tokens(char *message[]);

#endif //__UTILS__H__