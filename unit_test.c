#include <stdlib.h>
#include <stdio.h>
#include "mandelbrot.h"

int main(){

	MandelbrotData data = {NULL, {-0.5, 0}, 1000, 1620, 1080, 1, 1.5};
	data.iterationData = plotIterationsToEscape(data.center, data.iterations, data.res_x, data.res_y, data.scale, data.aspectRatio);
	mandelbrotDataToFile(data, "data.mbs");
	for (int i = 0; i < data.res_x; i++) free(data.iterationData[i]);
	free(data.iterationData);
	return 0;

}