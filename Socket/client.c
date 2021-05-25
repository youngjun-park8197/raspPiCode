// [ Client side ]

#include <stdio.h> // < ... > : system header folder
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h> // /usr/include/
#include <arpa/inet.h>

typedef struct sockaddr_in Socket; 

int main() {
	// 소켓 구조체 사용 -> sockaddr_in
	Socket sock;
	char buf[1024];

	scanf("%s", buf); // 입력 문자열 

	// 소켓(sock)의 정보들이 저장됨 
	/*AF_INET 구조체 유형 
	 *	struct sockaddr_in {
	 *		sa_family_t				sin_family;  -> AF_INET
	 *		in_port_t					sin_port;  -> port 번호 		 
	 *		struct	in_addr		sin_addr;  -> IP address
	 *	}
	 *
	 *Internet address
	 *	struct in_addr {
	 *		uint32_t		s_addr;  -> address in network byte order
	 *	}
	 */

	sock.sin_addr.s_addr = inet_addr("192.168.0.43"); // inet_addr을 통해 주소 전달
	sock.sin_port = 9001;
	
	int hndl = socket(AF_INET, SOCK_STREAM, 0); // AFINET : Address Family Internet type
	
	// 서버에 연결 요청
	connect(hndl, (struct sockaddr*)&sock, sizeof(sock)); // connect(hndl, sock의 주소, Socket 구조체의 size)
	
	// 서버 연결 수립 시, read / write 수행 가능
	write(hndl, buf, strlen(buf)); // write(hndl, 문자열, 문자열의 길이)
	close(hndl);
}
