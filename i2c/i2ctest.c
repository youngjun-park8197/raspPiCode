#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>


int main(int argc, char *argv[]) {
	/*
	 * int main(int argc, char *argv[])
	 * .... $ i2ctest 1 2 3
	 * ---> argc : 4, argv = { "i2ctest", "1", "2", "3" }
	 */

	int chan = 4; // 핀 모드 정의
	int ret = wiringPiSetup(); // 전구 연결 상태 초기 확인 
	pinMode(chan, OUTPUT); // pin 모드 선택
	printf("%d\n", ret); // wiringPiSetup 상태 출력 : 0일 경우 정상

	float val;
	int sens = atoi(argv[1]);

	if(argc < 2)  { printf("\nUsage : %s AIN_No \n\n", argv[0]); return 0; } // %s : 실행 파일명 (가장 첫번째 입력)
	
	int hndl = wiringPiI2CSetup(0x48); //i2c 모듈의 Handle return

	if(strcmp(argv[1], "0") == 0) // argv[1]이 0일 때, ch = 0
	{
		sens = 0; 
		printf("\n ********** 조도 센서 측정 ********** \n"); 
	}
	
	if(strcmp(argv[1], "1") == 0) 
	{ 
		sens = 1;
		printf("\n ********** 온도 센서 측정 ********** \n"); 
	}

	if(strcmp(argv[1], "3") == 0) 
	{ 
		sens = 3;
		printf("\n **********  센서 측정 ********** \n"); 
	}	

	// 채널 초기화 작업(반복해서 2, 3바이트 정도 버림)
	wiringPiI2CWrite(hndl, sens);
	wiringPiI2CRead(hndl);

	while(1) {
		val = wiringPiI2CRead(hndl);
		printf("%d\n", val);
		if(val >= 170) {
			digitalWrite(chan, HIGH);
		}
		else digitalWrite(chan, LOW);

		printf("read from I2C address [%d] : %f\n", sens, val);
		delay(500);
	}
}
