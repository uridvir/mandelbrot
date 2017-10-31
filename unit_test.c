#include <stdlib.h>
#include <stdio.h>
#include "ppm_output.h"

int main(){

	struct Color** colorMap = malloc(10 * sizeof(struct Color*));
	for (int i = 0; i < 10; i++) colorMap[i] = malloc(10 * sizeof(struct Color));

	for (int x = 0; x < 10; x++){
		for (int y = 0; y < 10; y++){
			struct Color* currentPixel = &colorMap[x][y];
			currentPixel->red = 4;
			currentPixel->green = 23;
			currentPixel->blue = 255;
		}
	}

	imageToFile(colorMap, 10, 10, "10x10.ppm");

	return 0;

}