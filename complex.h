struct Complex {
	double a, b;
};

typedef enum { false, true } bool;

struct Complex add(struct Complex x, struct Complex y){
	struct Complex result;
	result.a = x.a + y.a;
	result.b = x.b + y.b;
	return result;
}

struct Complex square(struct Complex x){
	struct Complex result;
	result.a = x.a * x.a - x.b * x.b;
	result.b = 2 * x.a * x.b;
	return result;
}