#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <math.h>

int main(){
	
	wiringPiSetup();
	if(wiringPiSPISetup(0,6000000)<0){
		printf("Failed to setup SPI!\n");
		return -1;
	}

	int a;
	uint8_t buffer0[1], buffer1[4];
	srand(time(NULL));

	while((1 != 2)){
		for(a=0; a<4; a++){
			buffer0[0]=0b00000000;
			wiringPiSPIDataRW(0, (unsigned char*)buffer0, 1);
		}
		for(a=0; a<304; a++){
			buffer1[0]=0b11111111;
			buffer1[1]=(uint8_t)(rand() % 256);
			buffer1[2]=(uint8_t)(rand() % 256);
			buffer1[3]=(uint8_t)(rand() % 256);
			wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
		}
		for(a=0; a<4; a++){
			buffer0[0]=0b11111111;
			wiringPiSPIDataRW(0, (unsigned char*)buffer0, 1);
		}
	}
	return 0;
}