#include <stdlib.h>
#include <stdio.h>
#include "ppm_output.h"

int main(){

	struct Palette palette;
	palette.numberOfColors = 4;
	palette.percentIterationsArray = malloc(palette.numberOfColors * sizeof(double));
	palette.colorArray = malloc(palette.numberOfColors * sizeof(struct Color));
	palette.percentIterationsArray[0] = 0;
	palette.percentIterationsArray[1] = 0.333;
	palette.percentIterationsArray[2] = 0.666;
	palette.percentIterationsArray[3] = 1;
	palette.colorArray[0] = (struct Color){0, 0, 0};
	palette.colorArray[1] = (struct Color){255, 0, 0};
	palette.colorArray[2] = (struct Color){0, 255, 0};
	palette.colorArray[3] = (struct Color){0, 0, 255};

	double totalIterations = 1000;

	struct Color** colorMap = malloc((totalIterations + 1) * sizeof(struct Color*));
	for (int i = 0; i < totalIterations + 1; i++) colorMap[i] = malloc((totalIterations + 1) * sizeof(struct Color));

	int iterations = 1;
	for (int i = 0; i < totalIterations + 1; i++){
		struct Color colorOfRow = pickColor(iterations, totalIterations, palette);
		for (int j = 0; j < totalIterations + 1; j++) colorMap[j][i] = colorOfRow;
		iterations++;
	}

	imageToFile(colorMap, totalIterations + 1, totalIterations + 1, "colors.ppm");

	free(palette.percentIterationsArray);
	free(palette.colorArray);
	for (int i = 0; i < totalIterations + 1; i++) free(colorMap[i]);
	free(colorMap);
	
	return 0;

}