// [ Client side ]

#include <stdio.h> // < ... > : system header folder
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
// #include <netinet/in.h> // /usr/include/

char *IP = "192.168.0.43";
int PORT = 9001;

int main() {
	int sock; // 소켓 변수 : 소켓에 대한 handle
	struct sockaddr_in sockinfo;
	char buf[1024];

	// socket connection을 위한 정보 정의
	sock = socket(AF_INET, SOCK_STREAM, 0); 
	sockinfo.sin_family = AF_INET;
	inet_pton(AF_INET, IP, &sockinfo.sin_addr.s_addr);
	sockinfo.sin_port = htons(PORT);

	// 연결
	connect(sock, (struct sockaddr*)&sockinfo, sizeof(sockinfo));
	
	while(1) 
	{	
		scanf("%s", buf); // 문자열 입력('q' 입력시 종료)
		if(buf[0] == 'q') { break; }
		
		send(sock, buf, strlen(buf), 0); // send(소켓의 핸들, 문자열, 문자열 길이);
	}

	close(sock); // 통신 종료
}




/*
typedef struct sockaddr_in Socket; 

int main() {
	
	// 소켓 구조체 사용 -> sockaddr_in
	Socket sock;
	char buf[1024];

	scanf("%s", buf); // 입력 문자열 

	// 소켓(sock)의 정보들이 저장됨 
	//AF_INET 구조체 유형 
	//	struct sockaddr_in {
	//		sa_family_t				sin_family;  -> AF_INET
	//		in_port_t					sin_port;  -> port 번호 		 
	//		struct	in_addr		sin_addr;  -> IP address
	//	}
	//
	//Internet address
	//	struct in_addr {
	//		uint32_t		s_addr;  -> address in network byte order
	//	}
	//

	sock.sin_addr.s_addr = inet_addr("192.168.0.43"); // inet_addr을 통해 주소 전달
	sock.sin_port = 9001;
	
	int hndl = socket(AF_INET, SOCK_STREAM, 0); // AFINET : Address Family Internet type
	
	// 서버에 연결 요청
	connect(hndl, (const struct sockaddr*)&sock, sizeof(sock)); // connect(hndl, sock의 주소, Socket 구조체의 size)
	
	// 서버 연결 수립 시, read / write 수행 가능
	send(hndl, buf, strlen(buf), 0); // write(hndl, 문자열, 문자열의 길이)
	// close(hndl);
	
}
*/


