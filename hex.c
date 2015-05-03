#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[]){
	
	wiringPiSetup();
	if(wiringPiSPISetup(0,500000)<0){
		printf("Failed to setup SPI!\n");
		return -1;
	}
	
	if(strlen(argv[1])<6){
		printf("FAIL! D:\n");
		return -1;
	}
	
	if(strlen(argv[1])>6){
		printf("FAIL! D:\n");
		return -1;
	}
	
	int a;
	char red[]="  ", green[]="  ", blue[]="  ";
	char hexcode[6];
	uint8_t buffer0[1], buffer1[4];
	
	strcpy(hexcode, argv[1]);
	red[0] = hexcode[0]; red[1] = hexcode[1];
	green[0] = hexcode[2]; green[1] = hexcode[3];
	blue[0] = hexcode[4]; blue[1] = hexcode[5];
	

	for(a=0; a<4; a++){
		buffer0[0]=0b00000000;
		wiringPiSPIDataRW(0, (unsigned char*)buffer0, 1);
	}
	
	for(a=0; a<304; a++){
		buffer1[0]=0b11111111;
		buffer1[1]=((char)strtol(blue,NULL,16));
		buffer1[2]=((char)strtol(green,NULL,16));
		buffer1[3]=((char)strtol(red,NULL,16));
		wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
	}
	
	for(a=0; a<4; a++){
		buffer0[0]=0b11111111;
		wiringPiSPIDataRW(0, (unsigned char*)buffer0, 1);
	}
	
	return 0;

}