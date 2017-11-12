typedef enum { false, true } bool;

typedef struct Complex {
	double a, b;
} Complex;

typedef struct Color {
	unsigned char red, green, blue;
} Color;

typedef struct Palette {
	double* iterationsArray;
	struct Color* colorArray;
	int numberOfColors;
} Palette;

typedef struct IterationData {
	double iterations;
	Complex valueAtEscape; 
} IterationData;

typedef struct MandelbrotData {
	IterationData** iterationData;
	Complex center;
	int iterations;
	int res_x;
	int res_y;
	double scale;
	double aspectRatio;
} MandelbrotData;