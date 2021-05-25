// [ Client side ]

#include <stdio.h> // < ... > : system header folder
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h> // /usr/include/

typedef struct sockaddr_in Socket; 

int main() {
	// 소켓 구조체 사용 -> sockaddr_in
	Socket sock;
	
	// 소켓(sock)의 address 정보들이 저장됨 
	sock.sin_addr = inet_addr("192.168.0.43"); // inet_addr을 통해 주소 전달
	sock.sin_port = 9001;
	int hndl = socket(AF_INET, SOCK_STREAM, 0); // AFINET : Address Family Internet type
	
	// 서버에 연결 요청
	connect(hndl, &sock, sizeof(sock)); // connect(hndl, sock의 주소, Socket 구조체의 size)
	
	// 서버 연결 수립 시, read / write 수행 가능
	
}
