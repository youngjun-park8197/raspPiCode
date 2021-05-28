// UDP communication network


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

char* IP;
int PORT;
struct sockaddr_in udp_info;
int sock;

int main(int argc, char** argv) 
{
	IP   = argv[1];
	PORT = atoi(argv[2]);
	char *fn = argv[3]; // 파일명
	char buf[512];
	
	FILE* fp = fopen(fn, "rb"); // b : binary(바이너리 타입 파일), 그대로 read
	
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	udp_info.sin_family = AF_INET;
	inet_pton(AF_INET, IP, &udp_info.sin_addr.s_addr);
	udp_info.sin_port = htons(PORT);
	
	while(fgets(buf, 512, fp)) // 한줄에서 한줄을 읽었을 때 읽어들인 문자 갯수를 리턴, 더이상 읽을 것이 없으면 -1 리턴
	{
		// int n = fscanf(fp, "%s", buf); // 문자열을 엔터가 있을 때까지만 되돌려줌(스페이스 X, 줄바꿈 수행 X)
		sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&udp_info, sizeof(udp_info));
		sendto(sock, "\r\n", 2, 0, (struct sockaddr*)&udp_info, sizeof(udp_info));
	}
	close(sock);
	fclose(fp);
}


