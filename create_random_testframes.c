#include <stdio.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
	if(argc < 2 || argc > 2){
		printf("usage: %s file\n", argv[0]);
		return -1;
	}

	FILE *fp = fopen(argv[1], "w");

	if(fp == NULL){
		printf("Error opening file \"%s\"!\n", argv[1]);
		return -1;
	}

	int delay=200, frames=1, leds=300, count;

	fwrite(&frames, 4, 1, fp);
	fwrite(&delay, 4, 1, fp);
	fwrite(&leds, 4, 1, fp);

	for(count = 0; count < leds; count++){
		fputc(255, fp);
		fputc(255, fp);
		fputc(255, fp);
	}

	fclose(fp);
	return 0;
}
