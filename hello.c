#include <stdio.h>
#include <malloc.h>
#include <string.h>

int chrFind(char *str, char chr);
int strLen(char *str);
char **Split(char *str, char chr);
int chrCount(char *str, char chr);
char *GetToken(int index, char *str, char chr);


int main() {
  char buf[256];
  int a, b, c;
  
  /* 
  scanf("%s", buf);
  FILE *fp = fopen(buf, "ab");
   */  

  return 0;
}


char *GetToken(int index, char *str, char chr) { // "123,456,789" deli ','
  char** ss = Split(str, chr);
  return *(ss + index);
}


char **Split(char *str, char chr) {
  char *s1 = malloc(strLen(str)); // get memory space
  char **s2 = malloc((chrCount(str, chr) + 1) * 4); // possible to leak memory space -> use [ free() ]
  strcpy(s1, str);
  int i = 1;
  *(s2 + 0) = s1;
  while(*s1) {
    if(*s1 == chr) {
      *s1 == 0;
      *(s2 + i++) = s1 + 1;     
    }
    s1++;
  }
  return s2;
}



