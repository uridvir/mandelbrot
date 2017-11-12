#include <stdio.h>
#include <string.h>
#include "types.h"

int digitsInNumber(unsigned char n){
	if (n < 10){
		return 1;
	}
	else if (n < 100){
		return 2;
	}
	else {
		return 3;
	}
}

void imageToFile(Color** colorMap, int res_x, int res_y, char* filename, char* comment){
	FILE* pOutputFile;
	pOutputFile = fopen(filename, "w");
	fprintf(pOutputFile, "P3\n");
	if (strlen(comment) > 0){
		fprintf(pOutputFile, "# %s\n", comment);
	}
	fprintf(pOutputFile, "%d %d\n", res_x, res_y);
	fprintf(pOutputFile, "%d\n", 255);
	int digits = 0;
	for (int y = 0; y < res_y; y++){
		for (int x = 0; x < res_x; x++){
			const Color currentPixel = colorMap[x][y];
			const int digitsOfPixel = digitsInNumber(currentPixel.red) + digitsInNumber(currentPixel.green) + digitsInNumber(currentPixel.blue) + 3;
			if (digits + digitsOfPixel > 70){
				fprintf(pOutputFile, "\n");
				digits = digitsOfPixel;
			}
			else {
				digits += digitsOfPixel;
			}
			fprintf(pOutputFile, "%d %d %d ", currentPixel.red, currentPixel.green, currentPixel.blue);
		}
	}
	fclose(pOutputFile);
}

double map(double n, double a, double b, double c, double d){
	if (a < b)      return (n - a) / (b - a) * (d - c) + c;
	else if (a > b) return (n - b) / (a - b) * (d - c) + c;
}

Color pickColor(double iterations, Palette palette){
	for (int i = 0; i < palette.numberOfColors; i++){
		if (iterations <= palette.iterationsArray[i]){
			if (i > 0){
				Color previousColor = palette.colorArray[i - 1];
				Color currentColor = palette.colorArray[i];
				Color result;
				result.red = map(iterations, palette.iterationsArray[i - 1], palette.iterationsArray[i], previousColor.red, currentColor.red);
				result.green = map(iterations, palette.iterationsArray[i - 1], palette.iterationsArray[i], previousColor.green, currentColor.green);
				result.blue = map(iterations, palette.iterationsArray[i - 1], palette.iterationsArray[i], previousColor.blue, currentColor.blue);
				return result;
			}
			else {
				return palette.colorArray[0];
			}
		}
	}
	return palette.colorArray[palette.numberOfColors - 1];
}

void mandelbrotDataToFile(MandelbrotData data, char* filename){
	FILE* pOutputFile;
	pOutputFile = fopen(filename, "w");
	fprintf(pOutputFile, "MBS\n");
	fprintf(pOutputFile, "center: %f + %fi\n", data.center.a, data.center.b);
	fprintf(pOutputFile, "iterations: %d\n", data.iterations);
	fprintf(pOutputFile, "scale: %f\n", data.scale);
	fprintf(pOutputFile, "aspect: %f\n", data.aspectRatio);
	fprintf(pOutputFile, "res: %d x %d\n\n", data.res_x, data.res_y);
	for (int y = 0; y < data.res_y; y++){
		for (int x = 0; x < data.res_x; x++){
			IterationData value = data.iterationData[x][y]; 
			fprintf(pOutputFile, "%f, %f + %fi; ", value.iterations, value.valueAtEscape.a, value.valueAtEscape.b);
			if ((y * data.res_x + x + 1) % 5 == 0 && (y != 0 || x != 0)) fprintf(pOutputFile, "\n");
		}
	}
	fclose(pOutputFile);
}