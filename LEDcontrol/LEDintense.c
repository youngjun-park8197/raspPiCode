// writedown for test raspberryPi contol
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <softPwm.h>


int main(int argc, char **argv) {
	if(argc < 3) { printf("\nUsage : %s wpi-No\n\n", argv[0]); return 0; }
	
	int pinNo = atoi(argv[1]);
	int pwmRange = 100;
	float val = 0.f;

	wiringPiSetup();
	pinMode(pinNo, OUTPUT); // 라즈베리파이의 메인보드 상에 핀 연결 번호 선택
	softPwmCreate(pinNo, 0, pwmRange); 

	// int check = 0;
	int hndl = wiringPiI2CSetup(0x48);
	
	wiringPiI2CWrite(hndl, 0);
	wiringPiI2CRead(hndl);

	// 엔터키 입력 시 Light On / Off
	while(1) {
		val = wiringPiI2CRead(hndl);
		// getchar(); // 엔터키 입력
			
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
		printf("\n outdoor Brightness value : %f \n", val);
		if(val >= 200)	
		{
			for(int i = 0; i < pwmRange; i++) {
				softPwmWrite(pinNo, i); // Dimming up
				delay(15);
			}
		}

		else
		{
			for(int i = pwmRange; i >= 0; i--) {
				softPwmWrite(pinNo, i); // Dimming down
				delay(15);
			}
		}	
	}
	return 0;
}

