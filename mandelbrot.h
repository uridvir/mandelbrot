#include <stdio.h>
#include <stdlib.h>
#include "data_io.h"

Complex** complexArrayPlot(int res_x, int res_y, double min_real, double max_real, double min_imag, double max_imag){
	const double spacing_x = (max_real - min_real) / (res_x - 1);
	const double spacing_y = (max_imag - min_imag) / (res_y - 1);
	Complex** result = malloc(res_x * sizeof(Complex*));
	for (int i = 0; i < res_x; i++) result[i] = malloc(res_y * sizeof(Complex));
	double x = min_real, y;
	for (int i = 0; i < res_x; i++){
		y = max_imag;
		for (int j = 0; j < res_y; j++){
			Complex point;
			point.a = x;
			point.b = y;
			result[i][j] = point;
			y -= spacing_y;
		}
		x += spacing_x;
	}
	return result;
}

IterationData iterationsToEscape(Complex x, int iterations){
	Complex z = {0, 0};
	for (int i = 0; i < iterations; i++){
		double squareRealZ = z.a * z.a, squareImagZ = z.b * z.b;
		double zRealTemp = squareRealZ - squareImagZ + x.a;
		z.b = 2 * z.a * z.b + x.b;
		z.a = zRealTemp;
		if (squareRealZ + squareImagZ > 4){
			IterationData result = {i, z};
			return result;
		}
	}
	IterationData result = {iterations};
	return result;
}

IterationData** plotIterationsToEscape(Complex center, int iterations, int res_x, int res_y, double scale, double aspectRatio){
    const double min_real = center.a - aspectRatio / scale;
    const double max_real = center.a + aspectRatio / scale;
    const double min_imag = center.b - 1 / scale;
    const double max_imag = center.b + 1 / scale;
    Complex** plot = complexArrayPlot(res_x, res_y, min_real, max_real, min_imag, max_imag);
    IterationData** result = malloc(res_x * sizeof(IterationData*));
    for (int i = 0; i < res_x; i++) result[i] = malloc(res_y * sizeof(IterationData));
    for (int x = 0; x < res_x; x++){
        for (int y = 0; y < res_y; y++){
        	result[x][y] = iterationsToEscape(plot[x][y], iterations);
        }
    }
    for (int i = 0; i < res_x; i++) free(plot[i]);
    free(plot);
    return result;
}

void plotConsole(MandelbrotData data){
	for (int y = 0; y < data.res_y; y++){
		for (int x = 0; x < data.res_x; x++){
			if (data.iterationData[x][y].iterations == data.iterations){
				printf("*");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

void colorPlotPicture(MandelbrotData data, char* pictureFilename, Palette palette){
	Color** colorMap = malloc(data.res_x * sizeof(Color*));
	for (int i = 0; i < data.res_x; i++) colorMap[i] = malloc(data.res_y * sizeof(Color));
	for (int x = 0; x < data.res_x; x++){
		for (int y = 0; y < data.res_y; y++){
			colorMap[x][y] = pickColor(data.iterationData[x][y].iterations, palette);
		}
	}
	char* comment = malloc(200 * sizeof(char));
	sprintf(comment, "Centered at %f + %fi, %d iterations, scale factor %f, aspect ratio %f, resolution %dx%d", data.center.a, data.center.b, data.iterations, data.scale, data.aspectRatio, data.res_x, data.res_y);
	imageToFile(colorMap, data.res_x, data.res_y, pictureFilename, comment);
	for (int i = 0; i < data.res_x; i++) free(colorMap[i]);
	free(colorMap);
}