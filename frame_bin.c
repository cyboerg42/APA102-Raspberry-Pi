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

	int a, frames, del, leds, count;
	uint8_t frame[3000], buffer[4], tmp[1];
	
	FILE * fp;
	fp = fopen (argv[1], "r");

	fread(&frames, 4, 1, fp);
	fread(&del, 4, 1, fp);
	fread(&leds, 4, 1, fp);

	printf("Frames: %d\nDelay: %d\nLEDs: %d", frames, del, leds);

	for(count = 0; count < frames; count++){
		fread(frame, 1, 3*leds, fp);
		tmp[0]=0;
		wiringPiSPIDataRW(0, (unsigned char*)tmp, 1);
		tmp[0]=0;
		wiringPiSPIDataRW(0, (unsigned char*)tmp, 1);
		tmp[0]=0;
		wiringPiSPIDataRW(0, (unsigned char*)tmp, 1);
		tmp[0]=0;		
		wiringPiSPIDataRW(0, (unsigned char*)tmp, 1);
	    
		for(a=0; a < (leds*3); a=a+3){
			buffer[0]=0b11111111;
			buffer[1]=frame[a+2];
			buffer[2]=frame[a+1];
			buffer[3]=frame[a];
			wiringPiSPIDataRW(0, (unsigned char*)buffer, 4);
		}
	
		tmp[0]=255;
		wiringPiSPIDataRW(0, (unsigned char*)tmp, 1);
		tmp[0]=255;
		wiringPiSPIDataRW(0, (unsigned char*)tmp, 1);
		tmp[0]=255;
		wiringPiSPIDataRW(0, (unsigned char*)tmp, 1);
		tmp[0]=255;		
		wiringPiSPIDataRW(0, (unsigned char*)tmp, 1);
		delay(del);
	}

	fclose(fp);
	
	return 0;

}
