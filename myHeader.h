#include <stdio.h>
#include <malloc.h>
#include <string.h>

int chrFind(char *str, char chr);
int strLen(char *str);
char **Split(char *str, char chr);
int chrCount(char *str, char chr);
char *GetToken(int index, char *str, char chr);
