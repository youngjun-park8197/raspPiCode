// gyroSense data transfer to DB using Socket

// [ Client side - connection ]

// socket connection header files define
#include <stdio.h> // < ... > : system header folder
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

// gyroSense header files define
#include <wiringPi.h>

char* IP = "192.168.0.43";
int PORT = 9001;

int main() {
	int wTrig = 15;
	int wEcho = 16;

	wiringPiSetup();
	
	pinMode(wTrig, OUTPUT);
	pinMode(wEcho, INPUT);

	int i, j, k;
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

	while(1) 
	{	
		digitalWrite(wTrig, LOW);
		delayMicroseconds(100);
		
		digitalWrite(wTrig, HIGH);
		delayMicroseconds(10);

		digitalWrite(wTrig, LOW);
		delayMicroseconds(200);
		
		while(digitalRead(wEcho) == LOW);
		long start = micros();

		while(digitalRead(wEcho) == HIGH);
		long end = micros();

		double dist = (end - start) * 0.17;
		
		printf("Disance calculation check :: Distance = %.3f mm \n", dist);

		delay(1000);

		sprintf(buf, "%f", dist); // dist 값을 받아 buf 배열에 넣어줌

		send(sock, buf, strlen(buf), 0); // send(소켓의 핸들, 문자열, 문자열 길이);
		i = recv(sock, buf, strlen(buf) - 1, 0); // blocking 모드, null이 들어가지 않는 문자열 처리

		if(i > 0) buf[i] = 0; // buf 문자열의 끝을 가리키는 경우 그 끝의 인덱스에 해당하는 값을 0으로 구분
	}

	close(sock); // 통신 종료
}


/*
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int main() {

	int wTrig = 15;
	int wEcho = 16;
	wiringPiSetup();

	pinMode(wTrig, OUTPUT); // 트리거는 내보내는 방향이므로 OUTPUT : 측정신호발사
	pinMode(wEcho, INPUT); // 반사 신호 검출
	

	while(1) {
		digitalWrite(wTrig, LOW);
		delayMicroseconds(100); // 트리거 신호를 위한 초기화 

		digitalWrite(wTrig, HIGH);
		delayMicroseconds(10); // 기본 밀리초 단위를 마이크로초로 변환해줌 : 10 us 의 트리거 신호
		digitalWrite(wTrig, LOW);
		delayMicroseconds(200); // 실제로 발사까지 200us의 지연시간이 필요

		while(digitalRead(wEcho) == LOW); // until HIGH : 처음에 LOW 상태이므로 수행
		long start = micros(); // 현재 시간의 마이크로초 단위 count
	
		while(digitalRead(wEcho) == HIGH); // until HIGH
		long end = micros();
	
		double dist = (end - start) * 0.17;

		printf("현재 시간의 마이크로 초 단위 : %ld\n", start);
		printf("현재 시간의 마이크로 초 단위 : %ld\n", end);
		printf("Distance : %.3fmm\n", dist);
		delay(1000);
	}
}


 */
