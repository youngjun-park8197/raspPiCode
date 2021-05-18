// writedown for test raspberryPi contol
#include <stdio.h>
#include <wiringPi.h>


main() {
	wiringPiSetup();
	PinMode(8, OUTPUT); // 라즈베리파이의 메인보드 상에 핀 연결 번호 선택

	int check = 0;
	// 엔터키 입력 시 Light On / Off
	while(1) {
		getchar(); // 엔터키 입력
		
		// 출력물 내보내기 : DigitalWrite( [핀번호], [신호수준] );
		// * 출력수준 예시
		// 5V ------------------------------------------- [ HIGH ] : VDD
		// 
		// 0V ------------------------------------------- [ LOW ] : GND
		if(check % 2 == 0) 
			{ DigitalWrite(8, HIGH); }
		else
			{ DigitalWrite(8, LOW); }
		check++;
	}
}
