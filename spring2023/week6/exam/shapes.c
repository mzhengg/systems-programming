#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define M_PI 3.14159265358979323846

enum shapes {Circle, Square, Triangle};

double area_circle(double r)
{
	return M_PI*r*r;
}
double area_square(double a)
{
	return a*a;
}
double area_equilateral_triangle(double a)
{
	return sqrt(3.)/4*a*a;
}
//finish the following line of code to initilize the function pointer array
double (*pf[3])(double a) = {area_circle, area_square, area_equilateral_triangle};

typedef struct type_tag{
    enum shapes s;
    double a;
    double (*pfunc)(double a);
	double area;
}shape;

//implement the following function

int shape_cmp(const void *a, const void *b)
{
    // TODO: not getting the area correctly, but everything else is correect
    double areaA = *(double *)a;
    double areaB = *(double *)b;

    // printf("area after: %f\n", areaA);
    // printf("area after: %f\n", areaB);
    
    if (areaA == areaB) {
        return 0;
    }
    else if (areaA > areaB) {
        return 1;
    }
    else {
        return -1;
    }
}

//Do not change the main function
int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("Usage: %s n\n", argv[0]);
		return -1;
	}
	int n = atoi(argv[1]);
	assert(n >= 1 && n <=1000);

	shape a[n];

	for(int i=0; i<n; i++)
	{
		a[i].s = i % 3;
		a[i].a = (double) (i+1);
		a[i].pfunc = pf[a[i].s];
		a[i].area = a[i].pfunc(a[i].a);
        // printf("area beginning: %f\n", a[i].area);
	}
	printf("before qsort:\n");
        for(int i=0; i<n; i++)
                printf("%d\t%lf\t%lf\n", a[i].s, a[i].a, a[i].area);
	qsort(a, n, sizeof(shape), shape_cmp);
	printf("after qsort:\n");
	for(int i=0; i<n; i++)
		printf("%d\t%lf\t%lf\n", a[i].s, a[i].a, a[i].area);
	return 0;
}
