// [ Client side ]

#include <stdio.h> // < ... > : system header folder
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
// #include <netinet/in.h> // /usr/include/

char* IP = "192.168.0.43";
int PORT = 9001;
int sock; // thread의 메소드에서도 접근 가능하도록 global 변수로 선언

int main() {
	int i, j, k;

	pthread_t readThread;
	int sock; // 소켓 변수 : 소켓에 대한 handle
	struct sockaddr_in sockinfo;
	char buf[1024];

	// socket connection을 위한 정보 정의
	sock = socket(AF_INET, SOCK_STREAM, 0); // socket open
	sockinfo.sin_family = AF_INET;
	inet_pton(AF_INET, IP, &sockinfo.sin_addr.s_addr);
	sockinfo.sin_port = htons(PORT);

	// 연결
	connect(sock, (struct sockaddr*)&sockinfo, sizeof(sockinfo));

	// 서버로부터 되돌아오는 값이 없지만 무시하고 다음단계로 갈 수 있도록 함(non-blocking)
	// Auto Ack 체크 후에 수행하면 ACK를 받음
	k = fcntl(sock, F_SETFL, 0);
	fcntl(sock, F_SETFL, k | O_NONBLOCK);
	
	pthread_create(&readThread, NULL, readProc, NULL); // thread가 생성과 동시에 실행에 들어간다

	while(1) 
	{	
		scanf("%s", buf); 
		if(buf[0] == 'q') break; // 문자열 입력('q' 입력시 종료)
		
		send(sock, buf, strlen(buf), 0); // send(소켓의 핸들, 문자열, 문자열 길이);
		i = recv(sock, buf, strlen(buf) - 1, 0); // blocking 모드

		if(i > 0) buf[i] = 0; // buf 문자열의 끝을 가리키는 경우 그 끝의 인덱스에 해당하는 값을 0으로 구분
		if(buf[0] == 'q') break; // 문자열 입력('q' 입력시 종료)
		

		printf("%s\n", buf);
	}

	close(sock); // 통신 종료
}


// thread 구성, thread내에 들어갈 함수 원형은 포인터로 선언
void* readProc() {
	int i;
	char buf[1024];

	while(1) 
	{
		i = recv(sock, buf, strlen(buf) - 1, 0); // main에 있는 sock를 사용해야함
		if(i > 0) buf[i] = 0; // buf 문자열의 끝을 가리키는 경우 그 끝의 인덱스에 해당하는 값을 0으로 구분
		printf("%s\n", buf);
		delay(500); // 0.5초 마다 한번씩 recv 버퍼를 감지해서 있으면 출력을 해줌
	}

	return NULL;
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


