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

	float val;
	int ch = atoi(argv[1]);

	if(argc < 2)  { printf("\nUsage : %s AIN_No \n\n", argv[0]); return 0; } // %s : 실행 파일명 (가장 첫번째 입력)
	
	int hndl = wiringPiI2CSetup(0x48); //i2c 모듈의 Handle return

	if(strcmp(argv[1], "0") == 0) // argv[1]이 0일 때, ch = 0
	{
		ch = 0; 
		printf("\n ********** 조도 센서 측정 ********** \n"); 
	}
	
	if(strcmp(argv[1], "1") == 0) 
	{ 
		ch = 1;
		printf("\n ********** 온도 센서 측정 ********** \n"); 
	}

	if(strcmp(argv[1], "3") == 0) 
	{ 
		ch = 3;
		printf("\n **********  센서 측정 ********** \n"); 
	}	

	wiringPiI2CWrite(hndl, ch);
	wiringPiI2CRead(hndl);

	while(1) {
		val = wiringPiI2CRead(hndl);
		printf("read from I2C address [0] : %f\n", val);
		delay(500);
	}
}
