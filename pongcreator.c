//Program to create a simple pong file with the new file format

#include <stdio.h>
#include <stdint.h>


int main(int argc, char *argv[]){

	if(argc < 2 || argc > 2){
		printf("usage: %s file\n", argv[0]);
		return -1;
	}

	FILE *fp = fopen(argv[1], "w");

	if(fp == NULL){
		printf("Error opening file \"%s\"!\n", argv[1]);
		return -1;
	}

	int delay=200, frames=600, leds=300, count, direction, tmp, pong = 0;
	char r = 255, g = 255, b = 255; 

	fwrite(&frames, 4, 1, fp);
	fwrite(&delay, 4, 1, fp);
	fwrite(&leds, 4, 1, fp);

	for(count = 0; count < frames; count++){
		if(pong == leds-1)
			if(direction == 0)
				direction = 1;
			else
				direction = 0;

		for(tmp = 0; tmp < leds; tmp++)
			if(pong == tmp){
				fputc(r, fp);
				fputc(b, fp);
				fputc(g, fp);
			}else{
				fputc(0, fp);
				fputc(0, fp);
				fputc(0, fp);
			}
		
		if(direction == 1)
			pong++;
		else
			pong--;
	}

	fclose(fp);

	return 0;

}
