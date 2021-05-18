#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "myHeader.h"


int main() {
  char buf[256];
  int a, b, c;
	char *s1 = "abcdefghijklmnopqrstuvwxyz";
	char *tt = "1,2,3,4,5,6";

	while(1) {
		printf("Input search num : ");
		scanf("%d", &a);
		strcpy(buf, GetToken(a, tt, ','));
		printf("%d 번째 아이템은 %s 입니다.\n", a, buf);
	}

  return 0;
}


int strLen(char *str) {
	int i = 0;
	while(*str++) i++;
	return i;
}


char *GetToken(int index, char *str, char chr) { // 2, "123,456,789" , deli ',' ===> "789"(expecting result)
  // char** ss = Split(str, chr);
  // return *(ss + index);
  
  char buf[1024]; // 1K 정도의 내부 버퍼 설정, stack 영역에 설정됨(재사용 : 안정성 보장 X)
  int i, j, k, n = 0; // n : start 위치
  
  // --- start 위치 계산
  for(i = 0; i < index - 1; i++) {
    k = chrFind(str+n, chr) + 1; // 최초에 계산되어 돌아오는 값은 3 (','의 위치까지) / +1 해서 ',' 다음 search 
    if(k == -1) return NULL; // 개수만큼 구분자가 존재하지 않을 때 null 리턴
    n += k + 1;
  }

  // --- 다음번 start 위치(',' 혹은 라인의 끝)까지 계산 (길이)
  j = chrFind(str+n, chr);
  if(j == -1) j = strlen(str);
	else j += n;
  
	strncpy(buf, str+n, j-n); // j-n : 끝점에서 시작점을 뺀 것
	buf[j-n] = 0; // strncpy : NULL 미처리하기 때문에 0으로 처리 필요

	printf("Input string : %s\n [%d] Item : %s\n", str, index, buf); 

	return buf;
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


/*
 * 문자열을 찾기 위해서는 구분자가 index만큼 있어야함
 * ex) index = 2일 경우, 순서상으로는 0(1번째), 1(2번째)로 인덱싱
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
	int i = 0;

	while(*str) {
		if(*str++ == chr) i++;
	}
	return i;
}




