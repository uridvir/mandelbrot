#include <stdio.h>

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

void imageToFile(struct Color** colorMap, int res_x, int res_y, char* filename){
	FILE* pOutputFile;
	pOutputFile = fopen(filename, "w");
	fprintf(pOutputFile, "P3\n");
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