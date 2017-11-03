#include <stdio.h>
#include <string.h>

struct Color {
	unsigned char red, green, blue;
};

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

void imageToFile(struct Color** colorMap, int res_x, int res_y, char* filename, char* comment){
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
			const struct Color currentPixel = colorMap[x][y];
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

struct Palette {
	double* percentIterationsArray;
	struct Color* colorArray;
	int numberOfColors;
};

double map(double n, double a, double b, double c, double d){
	if (a < b)      return (n - a) / (b - a) * (d - c) + c;
	else if (a > b) return (n - b) / (a - b) * (d - c) + c;
}

struct Color pickColor(double iterationsPassed, double totalIterations, struct Palette palette){
	const double percentOfTotalIterationsPassed = iterationsPassed / (totalIterations + 1);
	for (int i = 0; i < palette.numberOfColors; i++){
		if (percentOfTotalIterationsPassed <= palette.percentIterationsArray[i]){
			if (i > 0){
				struct Color previousColor = palette.colorArray[i - 1];
				struct Color currentColor = palette.colorArray[i];
				struct Color result;
				result.red = map(percentOfTotalIterationsPassed, palette.percentIterationsArray[i - 1], palette.percentIterationsArray[i], previousColor.red, currentColor.red);
				result.green = map(percentOfTotalIterationsPassed, palette.percentIterationsArray[i - 1], palette.percentIterationsArray[i], previousColor.green, currentColor.green);
				result.blue = map(percentOfTotalIterationsPassed, palette.percentIterationsArray[i - 1], palette.percentIterationsArray[i], previousColor.blue, currentColor.blue);
				return result;
			}
			else {
				return palette.colorArray[0];
			}
		}
	}
}
