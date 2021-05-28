#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int main() {

	int wTrig = 15;
	int wEcho = 16;
	int count = atoi(argv[1]);
	wiringPiSetup();

	pinMode(wTrig, OUTPUT); // 트리거는 내보내는 방향이므로 OUTPUT : 측정신호발사
	pinMode(wEcho, INPUT); // 반사 신호 검출
		
	for(int i = 0; i < count; i++)
	{
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
		delay(100);
	}
}

