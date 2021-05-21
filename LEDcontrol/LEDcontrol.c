// writedown for test raspberryPi contol
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

int main(int argc, char **argv) {
	if(argc < 2) { printf("\nUsage : %s wpi-No\n\n", argv[0]); return 0; }
	
	int pinNo = atoi(argv[1]);
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
		
		/*
		 * compiler -> binary 
		 * optimization : depends on run speed / code size ...
		 */

		if(check % 2 == 0)	
		{	
			for(int i = 0; i < pwmRange; i++) { // 속도 최적화 관점으로 전환 : 
				softPwmWrite(pinNo, i); // Dimming up
				delay(50);
			}
		}
		else
		{
			for(int i = pwmRange; i >= 0; i--) {
				softPwmWrite(pinNo, i); // Dimming down
				delay(30);
			}
		}	
		check++;
	}
	return 0;
}

