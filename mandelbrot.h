#include <stdio.h>
#include <stdlib.h>
#include "complex.h"
#include "ppm_output.h"

typedef enum { false, true } bool;

bool isBounded(struct Complex x){
	if (x.a * x.a + x.b * x.b <= 4){
		return true;
	} else {
		return false;
	}
}

struct Complex** complexArrayPlot(int res_x, int res_y, double min_real, double max_real, double min_imag, double max_imag){
	const double spacing_x = (max_real - min_real) / (res_x - 1);
	const double spacing_y = (max_imag - min_imag) / (res_y - 1);
	struct Complex** result = malloc(res_x * sizeof(struct Complex*));
	for (int i = 0; i < res_x; i++) result[i] = malloc(res_y * sizeof(struct Complex));
	double x = min_real, y;
	for (int i = 0; i < res_x; i++){
		y = max_imag;
		for (int j = 0; j < res_y; j++){
			struct Complex point;
			point.a = x;
			point.b = y;
			result[i][j] = point;
			y -= spacing_y;
		}
		x += spacing_x;
	}
	return result;
}

int iterationsToEscape(struct Complex x, int iterations){
	struct Complex z = {0, 0};
	for (int i = 0; i < iterations; i++){
		if (!isBounded(z)){
			return i;
		}
		else {
			z = add(square(z), x);
		}
	}
	return iterations + 1;
}

void plotConsole(struct Complex center, int iterations, int res_x, int res_y, double scale, double aspectRatio){
	const double min_real = center.a - aspectRatio / scale;
	const double max_real = center.a + aspectRatio / scale;
	const double min_imag = center.b - 1 / scale;
	const double max_imag = center.b + 1 / scale;
	struct Complex** plot = complexArrayPlot(res_x, res_y, min_real, max_real, min_imag, max_imag);
	for (int y = 0; y < res_y; y++){
		for (int x = 0; x < res_x; x++){
			if (iterationsToEscape(plot[x][y], iterations) > iterations){
				printf("*");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
	for (int i = 0; i < res_x; i++) free(plot[i]);
	free(plot);
}



void blackWhitePlotPicture(struct Complex center, int iterations, int res_x, int res_y, double scale, double aspectRatio, char* pictureFilename){
	const double min_real = center.a - aspectRatio / scale;
	const double max_real = center.a + aspectRatio / scale;
	const double min_imag = center.b - 1 / scale;
	const double max_imag = center.b + 1 / scale;
	const struct Color White = {255, 255, 255};
	const struct Color Black = {0, 0, 0};
	struct Complex** plot = complexArrayPlot(res_x, res_y, min_real, max_real, min_imag, max_imag);
	struct Color** colorMap = malloc(res_x * sizeof(struct Color*));
	for (int i = 0; i < res_x; i++) colorMap[i] = malloc(res_y * sizeof(struct Color));
	for (int x = 0; x < res_x; x++){
		for (int y = 0; y < res_y; y++){
			if (iterationsToEscape(plot[x][y], iterations) > iterations){
				colorMap[x][y] = Black;
			}
			else {
				colorMap[x][y] = White;
			}
		}
	}
	char* comment = malloc(200 * sizeof(char));
	sprintf(comment, "Centered at %f + %fi, scale factor %f, aspect ratio %f, resolution %dx%d", center.a, center.b, scale, aspectRatio, res_x, res_y);
	imageToFile(colorMap, res_x, res_y, pictureFilename, comment);
	free(comment);
	free(plot);
	for (int i = 0; i < res_x; i++) free(colorMap[i]);
	free(colorMap);
}

void colorPlotPicture(struct Complex center, int iterations, int res_x, int res_y, double scale, double aspectRatio, char* pictureFilename, struct Palette palette){
	const double min_real = center.a - aspectRatio / scale;
	const double max_real = center.a + aspectRatio / scale;
	const double min_imag = center.b - 1 / scale;
	const double max_imag = center.b + 1 / scale;
	struct Complex** plot = complexArrayPlot(res_x, res_y, min_real, max_real, min_imag, max_imag);
	struct Color** colorMap = malloc(res_x * sizeof(struct Color*));
	for (int i = 0; i < res_x; i++) colorMap[i] = malloc(res_y * sizeof(struct Color));
	for (int x = 0; x < res_x; x++){
		for (int y = 0; y < res_y; y++){
			colorMap[x][y] = pickColor(iterationsToEscape(plot[x][y], iterations), palette);
		}
	}
	char* comment = malloc(200 * sizeof(char));
	sprintf(comment, "Centered at %f + %fi, scale factor %f, aspect ratio %f, resolution %dx%d", center.a, center.b, scale, aspectRatio, res_x, res_y);
	imageToFile(colorMap, res_x, res_y, pictureFilename, comment);
	free(comment);
	free(plot);
	for (int i = 0; i < res_x; i++) free(colorMap[i]);
	free(colorMap);
}