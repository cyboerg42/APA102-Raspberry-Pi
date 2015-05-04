#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
//A new, better file format:
//32bit int framecount, 32bit int delay between frames, 32bit int count of LEDs per frame, frames (1byte R, 1byte G, 1byte B, ....)

int main(int argc, char *argv[]){
	
	wiringPiSetup();
	if(wiringPiSPISetup(0,6000000)<0){
		printf("Failed to setup SPI!\n");
		return -1;
	}

	int a, frames, delay, leds, count;
	uint8_t frame[900], buffer[4];
	
	FILE * fp;
	fp = fopen (argv[1], "r");

	fread(&frames, 4, 1, file);
	fread(&del, 4, 1, file);
	fread(&leds, 4, 1, file);

	for(count = 0; count < frames, count++){
		fread(frame, 1, 900, fp);

		wiringPiSPIDataRW(0, (unsigned char*)0b11111111, 1);
		wiringPiSPIDataRW(0, (unsigned char*)0b11111111, 1);
		wiringPiSPIDataRW(0, (unsigned char*)0b11111111, 1);
		wiringPiSPIDataRW(0, (unsigned char*)0b11111111, 1);
	    
		for(a=0; a < (leds*3); a=a+3){
			buffer[0]=0b11111111;
			buffer[1]=frame[a];
			buffer[2]=frame[a+1];
			buffer[3]=frame[a+2];
			wiringPiSPIDataRW(0, (unsigned char*)buffer, 4);
		}
	
		wiringPiSPIDataRW(0, (unsigned char*)0b11111111, 1);
		wiringPiSPIDataRW(0, (unsigned char*)0b11111111, 1);
		wiringPiSPIDataRW(0, (unsigned char*)0b11111111, 1);
		wiringPiSPIDataRW(0, (unsigned char*)0b11111111, 1);
		delay(delay);
	}

	fclose(fp);
	
	return 0;

}
