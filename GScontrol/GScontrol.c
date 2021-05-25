#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

short i2cInt16(int hndl, int addr);

int main() {
	int i2cAddr = 0x68;
	int bufAddr = 0x3b; // buffer register
	int pwrAddr = 0x6b; // power
	
	wiringPiSetup(); // 기본적으로 먼저 wiring 사용 시 setup 필요
	int hndl = wiringPiI2CSetup(i2cAddr); // i2c 인터페이스 사용을 위해서는 wiringPi에 i2c setup도 필요
	
	wiringPiI2CWriteReg8(hndl, pwrAddr, 0); // 해당 hndl의 pwrAddr 레지스터에 0을 보내면 측정 뒤 data 레지스터에 저장

	double x1, y1, z1, x2, y2, z2;

	// 1바이트 단위로 해주어야 정확도 상승
	while(1) {
		x1 = i2cInt16(hndl, bufAddr) / 16384.; // 16384를 사용하는 이유 : 2^14 로 나누는 것을 의미
		y1 = i2cInt16(hndl, bufAddr+2) / 16384.; // 16384를 사용하는 이유 : 2^14 로 나누는 것을 의미
		z1 = i2cInt16(hndl, bufAddr+4) / 16384.; // 16384를 사용하는 이유 : 2^14 로 나누는 것을 의미
		
		x2 = i2cInt16(hndl, bufAddr+8) / 131.; // 16384를 사용하는 이유 : 2^14 로 나누는 것을 의미
		y2 = i2cInt16(hndl, bufAddr+10) / 131.; // 16384를 사용하는 이유 : 2^14 로 나누는 것을 의미
		z2 = i2cInt16(hndl, bufAddr+12) / 131.; // 16384를 사용하는 이유 : 2^14 로 나누는 것을 의미

		printf("x1 = [ %f ], y1 = [ %f ], z1 = [ %f ], x2 = [ %f ], y2 = [ %f ], z2 = [ %f ]\n", x1, y1, z1, x2, y2, z2);

		delay(700);
	}

	// 같은 i2c 인터페이스를 사용하지만 읽는 방법이 상이함 
	// 총 6개의 메모리 블록을 사용(2개의 x, y, z 좌표계 사용)
}

short i2cInt16(int hndl, int addr) {
		short d1 = wiringPiI2CReadReg8(hndl, addr);
		short d2 = wiringPiI2CReadReg8(hndl, addr+1);
		short d3 = (d1 << 8) | d2;  // shift 연산 << 8 ( => * 256)
		return d3;
}

