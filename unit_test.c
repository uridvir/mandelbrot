#include <stdlib.h>
#include <stdio.h>
#include "mandelbrot.h"

int main(){

	struct Palette palette;
	palette.numberOfColors = 4;
	palette.iterationsArray = malloc(palette.numberOfColors * sizeof(double));
	palette.colorArray = malloc(palette.numberOfColors * sizeof(struct Color));
	palette.iterationsArray[0] = 0;
	palette.iterationsArray[1] = 100;
	palette.iterationsArray[2] = 800;
	palette.iterationsArray[3] = 1000;
	palette.colorArray[0] = (struct Color){0, 0, 128};
	palette.colorArray[1] = (struct Color){255, 255, 255};
	palette.colorArray[2] = (struct Color){255, 255, 255};
	palette.colorArray[3] = (struct Color){0, 0, 0};

	double iterations = 1000;
	struct Complex center = {-0.5, 0};

	colorPlotPicture(center, iterations, 1620, 1080, 1, 1.5, "mandelbrot_color_test.ppm", palette);

	free(palette.iterationsArray);
	free(palette.colorArray);
	
	return 0;

}