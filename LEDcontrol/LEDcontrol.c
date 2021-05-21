// writedown for test raspberryPi contol
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

int main() {
	int pinNo = 8;
	int pwmRange = 100;

	wiringPiSetup();
	pinMode(pinNo, OUTPUT); // 라즈베리파이의 메인보드 상에 핀 연결 번호 선택
	softPwmCreate(pinNo, 0, pwmRange); // 

	int check = 0;
	// 엔터키 입력 시 Light On / Off
	while(1) {
		getchar(); // 엔터키 입력
		
		// 출력물 내보내기 : DigitalWrite( [핀번호], [신호수준] );
		// * 출력수준 예시
		// 5V ------------------------------------------- [ HIGH ] : VDD
		// 
		// 0V ------------------------------------------- [ LOW ] : GND
		// if(check % 2 == 0)	digitalWrite(pinNo, HIGH);
		// else								digitalWrite(pinNo, LOW);

		if(check % 2 == 0)	
		{	
			for(int i = 0; i < pwmRange; i++) {
				softPwmWrite(pinNo, i); // Dimming up
			}
			softPwmWrite(pinNo, HIGH);
		}
		else
		{
			for(int i = 0; i < pwmRange; i++) {
				softPwmWrite(pinNo, pwmRange - i); // Dimming down
			}
		}	
		check++;
	}
	return 0;
}

