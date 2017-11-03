#include <stdlib.h>
#include <stdio.h>
#include "mandelbrot.h"

int main(){

	struct Palette palette;
	palette.numberOfColors = 4;
	palette.percentIterationsArray = malloc(palette.numberOfColors * sizeof(double));
	palette.colorArray = malloc(palette.numberOfColors * sizeof(struct Color));
	palette.percentIterationsArray[0] = 0;
	palette.percentIterationsArray[1] = 0.1;
	palette.percentIterationsArray[2] = 0.8;
	palette.percentIterationsArray[3] = 1;
	palette.colorArray[0] = (struct Color){0, 0, 128};
	palette.colorArray[1] = (struct Color){255, 255, 255};
	palette.colorArray[2] = (struct Color){255, 255, 255};
	palette.colorArray[3] = (struct Color){0, 0, 0};

	double iterations = 10000;
	struct Complex center = {-0.72, -0.22};

	colorPlotPicture(center, iterations, 1620, 1080, 30, 1.5, "mandelbrot_color_zoom2_10k.ppm", palette);

	free(palette.percentIterationsArray);
	free(palette.colorArray);
	
	return 0;

}