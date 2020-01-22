#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define LED_COUNT 300

int main(int argc, char *argv[])
{
	wiringPiSetup();
	if(wiringPiSPISetup(0,6000000)<0){
		printf("Failed to setup SPI!\n");
		return -1;
	}

	int a;
	uint8_t buffer0[1], buffer1[4];

	for(a=0; a<4; a++){
		buffer0[0]=0b00000000;
		wiringPiSPIDataRW(0, (unsigned char*)buffer0, 1);
	}

	FILE * fp;
	fp = fopen (argv[1], "r");

	for(a=0; a<LED_COUNT; a++){
		char red[2], green[2], blue[2];
		fscanf(fp, "%s %s %s ", red, green, blue);
		buffer1[0]=0b11111111;
		buffer1[1]=((char)strtol(blue,NULL,16));
		buffer1[2]=((char)strtol(green,NULL,16));
		buffer1[3]=((char)strtol(red,NULL,16));
		wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
	}

	fclose(fp);

	for(a=0; a<4; a++){
		buffer0[0]=0b11111111;
		wiringPiSPIDataRW(0, (unsigned char*)buffer0, 1);
	}

	return 0;
}
