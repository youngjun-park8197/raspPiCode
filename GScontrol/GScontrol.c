#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int main() {
	int i2cAddr = 0x68;
	int bufAddr = 0x3b; // buffer register
	int pwdAddr = 0x6b; // power
	
	wiringPiSetup(); // 기본적으로 먼저 wiring 사용 시 setup 필요
	int hndl = wiringPiI2CSetup(i2cAddr); // i2c 인터페이스 사용을 위해서는 wiringPi에 i2c setup도 필요
	
	wiringPiI2CWriteReg8(hndl, pwdAddr, 0); // 해당 hndl의 pwdAddr 레지스터에 0을 보내면 측정 뒤 data 레지스터에 저장

	int x1, y1, z1, x2, y2, z2;

	while(1) {
		x1 = wiringPiI2CReadReg16(hndl, bufAddr);
		y1 = wiringPiI2CReadReg16(hndl, bufAddr+2);
		z1 = wiringPiI2CReadReg16(hndl, bufAddr+4);
		x2 = wiringPiI2CReadReg16(hndl, bufAddr+8);
		y2 = wiringPiI2CReadReg16(hndl, bufAddr+10);
		z2 = wiringPiI2CReadReg16(hndl, bufAddr+12);

		printf("x1 = [ %d ], y1 = [ %d ], z1 = [ %d ]\n", x1, y1, z1);
		printf("x2 = [ %d ], y2 = [ %d ], z2 = [ %d ]\n\n", x2, y2, z2);
	}

	// 같은 i2c 인터페이스를 사용하지만 읽는 방법이 상이함 
	// 총 6개의 메모리 블록을 사용(2개의 x, y, z 좌표계 사용)
}
