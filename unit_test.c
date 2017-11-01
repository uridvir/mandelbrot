#include <stdlib.h>
#include <stdio.h>
#include "ppm_output.h"

int main(){

	const int n = 50;

	struct Color** colorMap = malloc(n * sizeof(struct Color*));
	for (int i = 0; i < n; i++) colorMap[i] = malloc(n * sizeof(struct Color));

	for (int x = 0; x < n; x++){
		for (int y = 0; y < n; y++){
			colorMap[x][y].red = 255;
			colorMap[x][y].green = 255;
			colorMap[x][y].blue = 255;
		}
	}

	char* filename = malloc(50 * sizeof(char));
	sprintf(filename, "%dx%d.ppm", n, n);

	imageToFile(colorMap, n, n, filename);

	free(colorMap);
	free(filename);

	return 0;

}