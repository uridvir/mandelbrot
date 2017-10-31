bool isBounded(struct Complex x){
	if (x.a * x.a + x.b * x.b <= 4){
		return true;
	} else {
		return false;
	}
}

bool inMandelbrotSet(struct Complex x, int iterations){
	struct Complex z;
	z.a = 0;
	z.b = 0;
	for (int i = 0; i < iterations; i++){
		if (!isBounded(z)) {
			return false;
		} else {
			z = add(square(z), x);
		}
	}
	return true;
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

void plotConsole(struct Complex center, int iterations, int res_x, int res_y, double scale, double aspectRatio){
	const double min_real = center.a - aspectRatio / scale;
	const double max_real = center.a + aspectRatio / scale;
	const double min_imag = center.b - 1 / scale;
	const double max_imag = center.b + 1 / scale;
	struct Complex** plot = complexArrayPlot(res_x, res_y, min_real, max_real, min_imag, max_imag);
	for (int y = 0; y < res_y; y++){
		for (int x = 0; x < res_x; x++){
			if (inMandelbrotSet(plot[x][y], iterations)){
				printf("*");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
}

int iterationsToEscape(struct Complex x, int iterations){
	struct Complex z;
	z.a = 0;
	z.b = 0;
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

int** plotIterationsToEscape(struct Complex center, int iterations, int res_x, int res_y, double scale, double aspectRatio){
	const double min_real = center.a - aspectRatio / scale;
	const double max_real = center.a + aspectRatio / scale;
	const double min_imag = center.b - 1 / scale;
	const double max_imag = center.b + 1 / scale;
	struct Complex** plot = complexArrayPlot(res_x, res_y, min_real, max_real, min_imag, max_imag);
	int** result = malloc(res_x * sizeof(int*));
	for (int i = 0; i < res_x; i++) result[i] = malloc(res_y * sizeof(int));
	for (int x = 0; x < res_x; x++){
		for (int y = 0; y < res_y; y++){
			result[x][y] = iterationsToEscape(plot[x][y], iterations);
		}
	}
	return result;
}