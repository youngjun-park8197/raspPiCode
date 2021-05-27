// TCP Server side 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int sock, sock_cli;
int PORT = 9001;
struct sockaddr_in sockinfo, sockinfo_cli;
char buf[1024]; // 1K


int main() {
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

	while(1) {
		printf("Input text : ");
		scanf("%s", buf); // 값 입력, accept 모드 대기 상태
		if(buf[0] == 'q') break; 
		send(sock_cli, buf, strlen(buf), 0); // 입력된 내용을 socket client로 내보내줌
	}
	close(sock);
}
