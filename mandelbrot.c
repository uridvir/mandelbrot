#include "mandelbrot.h"
#include <string.h>
#include <time.h>

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

	Complex center = {-0.5, 0};
	int iterations = 1000;
	int con_res_x = 210;
	int con_res_y = 65;
	double scale = 1;
	double aspectRatio = 1.5;
	PlottingMode mode = Console;
	char* pictureFilename = "data.ppm";
	double pic_res_x = 1620;
	double pic_res_y = 1080;
	Palette palette;
	palette.numberOfColors = 4;
	palette.iterationsArray = malloc(palette.numberOfColors * sizeof(double));
	palette.colorArray = malloc(palette.numberOfColors * sizeof(Color));
	palette.iterationsArray[0] = 0;
	palette.iterationsArray[1] = 100;
	palette.iterationsArray[2] = 800;
	palette.iterationsArray[3] = 1000;
	palette.colorArray[0] = (Color){0, 0, 128};
	palette.colorArray[1] = (Color){255, 255, 255};
	palette.colorArray[2] = (Color){255, 255, 255};
	palette.colorArray[3] = (Color){0, 0, 0};

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
		else if ((strcmp(argv[i], "-consoleresolution") == 0 || strcmp(argv[i], "-cr") == 0) && i + 2 < argc && isNumber(argv[i + 1]) && isNumber(argv[i + 2])){
			con_res_x = atoi(argv[i + 1]);
			con_res_y = atoi(argv[i + 2]);
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
		else if (strcmp(argv[i], "-console") == 0 || strcmp(argv[i], "-cmd") == 0){
			mode = Console;
			i++;
		}
		else if ((strcmp(argv[i], "-picture") == 0 || strcmp(argv[i], "-pic") == 0) && i + 1 < argc){
			mode = Picture;
			pictureFilename = argv[i + 1];
			i += 2;
		} 
		else if (strcmp(argv[i], "--help") == 0){
			printf("Uri's Mandelbrot set program\n\n");

			printf("Usage:\n");
			printf("mandelbrot [-console] [-picture file] [-center a b] [-iterations i] [-resolution x y] [-pictureresolution x y] [-scale s] [-aspectratio a]\n\n");

			printf("-center                 Set center coordinates (shortcut is -c)\n");
			printf("-iterations             Set iterations for each pixel in set (shortcut is -i)\n");
			printf("-consoleresolution      Set resolution of image in console mode (shortcut is -cr)\n");
			printf("-pictureresolution      Set resolution of image in picture mode (shortcut is -pr)\n");
			printf("-scale                  Set scale (zoom) of image (shortcut is -s)\n");
			printf("-aspectratio            Set aspect ratio of image (shortcut is -a)\n");
			printf("--help                  Display this help menu\n");
			printf("-console                Set program to plot on the console (shortcut is -cmd) (console mode is the default)\n");
			printf("-picture                Set program to plot in an image (shortcut is -pic)\n\n");

			printf("All the commands are optional. If an argument is ommitted, then the programmed default will be used. Also, the commands may be used in any order.");
			return 0;
		}
		else {
			printf("Those aren't valid arguments! Type \"mandelbrot --help\" for more information.");
			return -1;
		}
	}
	
	time_t timeBefore = time(0);
	IterationData** iterationData;
	MandelbrotData data = {NULL, center, iterations, 0, 0, scale, aspectRatio};

	switch (mode){
		case Console:
			iterationData = plotIterationsToEscape(center, iterations, con_res_x, con_res_y, scale, aspectRatio);
			data.iterationData = iterationData;
			data.res_x = con_res_x;
			data.res_y = con_res_y;
			plotConsole(data);
			for (int i = 0; i < con_res_x; i++) free(iterationData[i]);
			free(iterationData);
			break;
		case Picture:
			iterationData = plotIterationsToEscape(center, iterations, pic_res_x, pic_res_y, scale, aspectRatio);
			data.iterationData = iterationData;
			data.res_x = pic_res_x;
			data.res_y = pic_res_y;
			colorPlotPicture(data, pictureFilename, palette);
			for (int i = 0; i < pic_res_x; i++) free(iterationData[i]);
			free(iterationData);
			break;
	}

	time_t timeAfter = time(0);
	printf("Elapsed time %d seconds.", timeAfter - timeBefore);

	free(palette.iterationsArray);
	free(palette.colorArray);

	return 0;
}