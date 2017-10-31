#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "complex.h"
#include "mandelbrot.h"
#include "ppm_output.h"

bool isNumber(char* str){
	for (int i = 0; i < strlen(str); i++){
		switch (str[i]){
			case '0': 
				break;
			case '1': 
				break;
			case '2': 
				break;
			case '3': 
				break;
			case '4': 
				break;
			case '5': 
				break;
			case '6': 
				break;
			case '7': 
				break;
			case '8': 
				break;
			case '9': 
				break;
			case '.': 
				break;
			case '-':
				break;
			default: 
				return false;
		}
		return true;
	}
}

int main(int argc, char* argv[]){

	typedef enum { Console, Picture } PlottingMode;

	struct Complex center;
	center.a = -0.5;
	center.b = 0;
	int iterations = 1000;
	int res_x = 210;
	int res_y = 65;
	double scale = 1;
	double aspectRatio = 1.5;
	PlottingMode mode = Console;
	char* pictureFilename = "data.ppm";
	double pic_res_x = 1620;
	double pic_res_y = 1080;

	int i = 1;
	while (i < argc){
		if ((strcmp(argv[i], "-center") == 0 || strcmp(argv[i], "-c") == 0) && i + 2 < argc && isNumber(argv[i + 1]) && isNumber(argv[i + 2])){
			center.a = atof(argv[i + 1]);
			center.b = atof(argv[i + 2]);
			i += 3;
		}
		else if ((strcmp(argv[i], "-iterations") == 0 || strcmp(argv[i], "-i") == 0) && i + 1 < argc && isNumber(argv[i + 1])){
			iterations = atoi(argv[i + 1]);
			i += 2;
		}
		else if ((strcmp(argv[i], "-resolution") == 0 || strcmp(argv[i], "-r") == 0) && i + 2 < argc && isNumber(argv[i + 1]) && isNumber(argv[i + 2])){
			res_x = atoi(argv[i + 1]);
			res_y = atoi(argv[i + 2]);
			i += 3;
		}
		else if ((strcmp(argv[i], "-pictureresolution") == 0 || strcmp(argv[i], "-pr") == 0) && i + 2 < argc && isNumber(argv[i + 1]) && isNumber(argv[i + 2])){
			pic_res_x = atoi(argv[i + 1]);
			pic_res_y = atoi(argv[i + 2]);
			i += 3;
		}
		else if ((strcmp(argv[i], "-scale") == 0 || strcmp(argv[i], "-s") == 0) && i + 1 < argc && isNumber(argv[i + 1])){
			scale = atof(argv[i + 1]);
			i += 2;
		}
		else if ((strcmp(argv[i], "-aspectratio") == 0 || strcmp(argv[i], "-a") == 0) && i + 1 < argc && isNumber(argv[i + 1])){
			aspectRatio = atof(argv[i + 1]);
			i += 2;
		}
		else if (str(argv[i], "-console") == 0 || strcmp(argv[i], "-cmd")){
			plottingMode = Console;
			i++;
		}
		else if ((strcmp(argv[i], "-picture") == 0 || strcmp(argv[i], "-pic") == 0) && i + 1 < argc){
			plottingMode = Picture;
			pictureFilename = argv[i + 1];
			i += 2;
		} 
		else if (strcmp(argv[i], "--help") == 0){
			printf("Uri's Mandelbrot set program\n\n");

			printf("Usage:\n");
			printf("mandelbrot [-console] [-picture file] [-center a b] [-iterations i] [-resolution x y] [-pictureresolution x y] [-scale s] [-aspectratio a]\n\n");

			printf("-center          Set center coordinates (shortcut is -c)\n");
			printf("-iterations      Set iterations for each pixel in set (shortcut is -i)\n");
			printf("-resolution      Set resolution of image (shortcut is -r)\n");
			printf("-scale           Set scale (zoom) of image (shortcut is -s)\n");
			printf("-aspectratio     Set aspect ratio of image (shortcut is -a)\n");
			printf("--help           Display this help menu\n");
			printf("-console         Set program to plot on the console (shortcut is -cmd) (console mode is the default)\n");
			printf("-picture         Set program to plot in an image (shortcut is -pic)\n\n");

			printf("All the commands are optional. If an argument is ommitted, then the programmed default will be used. Also, the commands may be used in any order.");
			return 0;
		}
		else {
			printf("Those aren't valid arguments! Type \"mandelbrot --help\" for more information.");
			return -1;
		}
	}
	
	time_t timeBefore = time(0);

	switch (mode){
		case Console:
			plotConsole(center, iterations, res_x, res_y, scale, aspectRatio);
			break;
		case Picture:
			//plotPicture(center, iterations, pic_res_x, pic_res_y, scale, aspectRatio, pictureFilename);
			break;
	}

	time_t timeAfter = time(0);
	printf("Elapsed time %d seconds.", timeAfter - timeBefore);

	return 0;
}