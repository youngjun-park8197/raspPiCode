// UDP communication network


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

void* readProc();

int PORT = 9100;
struct sockaddr_in sockinfo_sv, sockinfo_cli;
int sock_sv, sock_cli;
int f_cli = 0;

int main() 
{
	char buf[512];

	pthread_t readThread;
	// 소켓 생성
	sock_sv = socket(AF_INET, SOCK_DGRAM, 0);
	sock_cli = socket(AF_INET, SOCK_DGRAM, 0);
	sockinfo_sv.sin_family = AF_INET;
	sockinfo_sv.sin_addr.s_addr = htonl(INADDR_ANY);
	sockinfo_sv.sin_port = htons(PORT);
	
	bind(sock_sv, (struct sockaddr*)&sockinfo_sv, sizeof(sockinfo_sv));

	pthread_create(&readThread, NULL, readProc, NULL); // thread 개시, 접속 요청이 있을 때에만 클라이언트 소켓에 대한 정보를 완성할 수 있음

	printf("standing by remote message ... \n\n"); // 외부로부터의 접속을 기다린다는 문장을 출력

	while(1) 
	{
		if(f_cli)
		{	
			printf("input text (0x%08x) : ");
			scanf("%s", buf);
			sockinfo_cli.sin_port = htons(PORT);
			sendto(sock_cli, buf, strlen(buf), 0, (struct sockaddr*)&sockinfo_cli, sizeof(sockinfo_cli));
		}
		// delay(100);
	}
}


void* readProc() 
{
	char buf[512];

	while(1) 
	{
		int n = sizeof(sockinfo_cli);
		int count = recvfrom(sock_sv, buf, 512, 0, (struct sockaddr*)&sockinfo_cli, &n);
		if(count > 0) 
		{
			buf[count] = 0;
			printf("%s\n", buf);
			f_cli = 1;
		}
	}
}
