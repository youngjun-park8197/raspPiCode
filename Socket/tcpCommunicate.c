// TCP Server side 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <pthread.h>

void* readProc();

int sock, sock_cli;
int PORT = 9001;
struct sockaddr_in sockinfo, sockinfo_cli;
char buf[1024]; // 1K

int main() {
	pthread_t readThread;
	
	// 소켓 생성(handle을 활용)
	sock = socket(AF_INET, SOCK_STREAM, 0);

	//sockinfo 정의
	sockinfo.sin_family = AF_INET;
	sockinfo.sin_addr.s_addr = htonl(INADDR_ANY); // 어디에서든 접속 가능함을 의미
	sockinfo.sin_port = htons(PORT);

	bind(sock, (struct sockaddr*)&sockinfo, sizeof(sockinfo)); // socket bind를 위한 선언

	listen(sock, 100);
	
	int n = sizeof(sockinfo_cli);
	sock_cli = accept(sock, (struct sockaddr*)&sockinfo_cli, &n); // blocking

	pthread_create(&readThread, NULL, readProc, NULL); // 스레드를 구성할 떄 어느 시점에 잡아주느냐를 고려해야함
	
	while(1) 
	{
		printf("input text : ");
		scanf("%s", buf); // 값 입력, accept 모드 대기 상태
		if(buf[0] == 'q') break; 
		send(sock_cli, buf, strlen(buf), 0); // 입력된 내용을 socket client로 내보내줌
		
		/*
		i = recv(sock_cli, buf, 1024, 0);
		if(i > 0) buf[i] = 0;
		if(buf[0] == 'q') break;
		printf("%s\n", buf);
		*/
	}
	close(sock);
}

void* readProc() {
	int i;
	char buf1[1024]; // 스레드 안에서 사용하는 공간과 메모리에서 사용하는 공간 끼리 구분 
	while(1) 
	{
		i = recv(sock_cli, buf1, 1024, 0); // 버퍼라는 메모리에 값을 넣어주기만 하는 것, 문자열의 끝을 알려주진 않음
		if(i > 0) buf1[i] = 0; // 문자열의 끝을 알려주는 작업
		if(buf1[0] == 'q') break; // 키보드에서 사용자 입력이 아닌 상대방 Endpoint에서 종료 요청
		printf("message(client) : %s\n", buf1); // console 출력
	}
}
