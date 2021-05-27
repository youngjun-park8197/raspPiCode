// UDP communication network


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

char* IP = "192.168.0.43";
int PORT = 9200;
struct sockaddr_in udp_info;
int sock;


int main() {
	char buf[512];

	// 소켓 생성
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	udp_info.sin_family = AF_INET;
	inet_pton(AF_INET, IP, &udp_info.sin_addr.s_addr);
	udp_info.sin_port = htons(PORT);

	send(sock, buf, strlen(buf), 0);

	while(1) {
		printf("input text: ");
		scanf("%s", buf);
		if(buf[0] == 'q') break;
		sendto(sock, buf, strlen(buf), 0, (struct sockaddr*)&udp_info, sizeof(udp_info));
	}
}

