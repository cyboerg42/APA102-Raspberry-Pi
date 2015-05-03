#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


int main(){
	
	wiringPiSetup();
	if(wiringPiSPISetup(0,6000000)<0){
		printf("Failed to setup SPI!\n");
		return -1;
	}
	
	int a;
	int b;
	int c;
	int d;
	uint8_t buffer0[1], buffer1[4];
	
	d = 0;
	c = 280;
	
	while((1 != 2)){	
		if(d==0){	
			for(a=0; a<4; a++){
				buffer0[0]=0b00000000;
				wiringPiSPIDataRW(0, (unsigned char*)buffer0, 1);
			}
			for(a=0; a<10; a++){
				buffer1[0]=0b11111111;
				buffer1[1]=0;
				buffer1[2]=0;
				buffer1[3]=255;
				wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
			}
			for(a=0; a<(280-c); a++){
				buffer1[0]=0b11111111;
				buffer1[1]=0;
				buffer1[2]=0;
				buffer1[3]=0;
				wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
			}
			for(b=0; b<1; b++){
					buffer1[0]=0b11111111;
					buffer1[1]=255;
					buffer1[2]=0;
					buffer1[3]=0;
					wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
					c = c - 1;
			}
			for(a=0; a<c; a++){
				buffer1[0]=0b11111111;
				buffer1[1]=0;
				buffer1[2]=0;
				buffer1[3]=0;
				wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
			}
			for(a=0; a<10; a++){
				buffer1[0]=0b11111111;
				buffer1[1]=0;
				buffer1[2]=0;
				buffer1[3]=254;
				wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
			}
			for(a=0; a<4; a++){
				buffer0[0]=0b11111111;
				wiringPiSPIDataRW(0, (unsigned char*)buffer0, 1);
			}
			if(c==0){
					c = 280;
					d = 1;
			}
		}	
		if(d!=0){
			for(a=0; a<4; a++){
				buffer0[0]=0b00000000;
				wiringPiSPIDataRW(0, (unsigned char*)buffer0, 1);
			}
			for(a=0; a<10; a++){
				buffer1[0]=0b11111111;
				buffer1[1]=0;
				buffer1[2]=0;
				buffer1[3]=255;
				wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
			}	
			for(a=0; a<c; a++){
				buffer1[0]=0b11111111;
				buffer1[1]=0;
				buffer1[2]=0;
				buffer1[3]=0;
				wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
			}
			for(b=0; b<1; b++){
					buffer1[0]=0b11111111;
					buffer1[1]=255;
					buffer1[2]=0;
					buffer1[3]=0;
					wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
					c = c - 1;
			}		
			for(a=0; a<(278-c); a++){
				buffer1[0]=0b11111111;
				buffer1[1]=0;
				buffer1[2]=0;
				buffer1[3]=0;
				wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
			}		
			for(a=0; a<10; a++){
				buffer1[0]=0b11111111;
				buffer1[1]=0;
				buffer1[2]=0;
				buffer1[3]=254;
				wiringPiSPIDataRW(0, (unsigned char*)buffer1, 4);
			}
			for(a=0; a<4; a++){
				buffer0[0]=0b11111111;
				wiringPiSPIDataRW(0, (unsigned char*)buffer0, 1);
			}
			if(c==0){
				c = 280;
				d = 0;
			}
		}
	}
	return 0;
}