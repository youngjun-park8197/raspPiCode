#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

int main() {
	int i2cAddr = 0x68;
	int bufAddr = 0x3b;

	// 같은 i2c 인터페이스를 사용하지만 읽는 방법이 상이함 
	// 총 6개의 메모리 블록을 사용(2개의 x, y, z 좌표계 사용)
}
