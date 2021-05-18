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


int strLen(char *str) {

}


char *GetToken(int index, char *str, char chr) { // 2, "123,456,789" , deli ',' ===> "789"(expecting result)
  // char** ss = Split(str, chr);
  // return *(ss + index);
  
  char buf[1024]; // 1K 정도의 내부 버퍼 설정 : 사용이 끝나는대로 free
  int i, j, k, n = 0; // n : start 위치
  
  // --- start 위치 계산
  for(i = 0; i < index; i++) {
    k = chrFind(str+n, chr) + 1; // 최초에 계산되어 돌아오는 값은 3 (','의 위치까지) / +1 해서 ',' 다음 search 
    if(k == -1) return NULL;
    n += k + 1;
  }

  // --- 다음번 start 위치(',' 혹은 라인의 끝)까지 계산 (길이)
  j = chrFind(str+n, chr);
  if(j == -1) j = strLen(str);  
  j += n;
  
  strcpy(buf, str+n, j-n); // j-n : 끝점에서 시작점을 뺀 것
	return buf;
}


/* 
 * 
 *
 */

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


/*
 * 문자열을 찾기 위해서는 구분자가 index만큼 있어야함
 * ex) index = 2일 경우, 순서상으로는 0(1번째), 1(2번째)로 인덱싱ㅁ
 * 1. chr의 index번째 위치를 찾는다
 * 2. 그 위치에서 다음번 chr의 위치까지를 복사해서 return
 *
 */
char chrFind(char *str, char chr) {
  int i = 0;
  while(*str) {
    if(*str++ == chr) return i;
    i++;
  }
  return -1;
}


int chrCount(char *str, char chr) {

}




