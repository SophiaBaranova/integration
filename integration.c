#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

double f(double x); //given function
double rectangle(double a, double b, int m); //rectangle rule
double trapezoidal(double a, double b, int m); //trapezoidal rule
double simpson(double a, double b, int m); //simpson's rule
void error(int code); //handle errors

int main()
{
	double a, b; //ends of the interval
	double e; //accuracy
	double h; //length of subintervals
	double I1, I2; //integrals
	double R; //calculation error
	int i, m, e_out, numb_steps, ans = 1, err = 0; //counters
	while (ans == 1)
	{
		printf("NUMERICAL INTEGRATION\n");
		printf("function f(x) = (x^3 + 4,5) / (x^4 + 5,1)\n");
		//enter the integration interval and desired accuracy
		do
		{
			printf("ends of the integration interval (using space) -> ");
			scanf("%lf%lf", &a, &b);
			printf("desired accuracy (number of digits after the decimal point) -> ");
			scanf("%d", &e_out);
			//calculate accuracy
			e = 1;
			for (i = 0; i < e_out; i++)
			{
				e /= 10;
			}
		} while (fabs(b - a) <= e);
		m = 1;
		//initial length of subintervals
		h = (b - a) / (2 * m);
		R = 10;
		numb_steps = 0;
		//choose the integration method
		printf("method:\n1 - rectangle rule\n2 - trapezoidal rule\n3 - Simpson's rule\n-> ");
		scanf("%d", &ans);
		switch (ans)
		{
		case 1:
			//rectangle rule
			I2 = rectangle(a, b, m);
			while (R >= e)
			{
				I1 = I2;
				m *= 2;
				I2 = rectangle(a, b, m);
				R = fabs(I1 - I2) / 3;
				numb_steps++;
			}
			break;
		case 2:
			//trapezoidal rule
			I2 = trapezoidal(a, b, m);
			while (R >= e)
			{
				I1 = I2;
				m *= 2;
				I2 = trapezoidal(a, b, m);
				R = fabs(I1 - I2) / 3;
				numb_steps++;
			}
			break;
		case 3:
			//simpson's rule
			I2 = simpson(a, b, m);
			while (R >= e)
			{
				I1 = I2;
				m *= 2;
				I2 = simpson(a, b, m);
				R = fabs(I1 - I2) / 3;
				numb_steps++;
			}
			break;
		default:
			printf("invalid answer\n");
			err = 1;
		}
		if (!err)
		{
			//print results
			printf("integral I = %.*lf\ncalculation R = %lg\nnumber of steps = %d\n", e_out, I1, R, numb_steps);
		}
		printf("continue?\n1 - yes\n2 - no\n-> ");
		scanf("%d", &ans);
	}
	return 0;
}

double f(double x)
{
	return (pow(x, 3) + 4.5) / (pow(x, 4) + 5.1);
}

double rectangle(double a, double b, int m)
{
	int i;
	//length of subintervals
	double h = (b - a) / (2 * m);
	double x, s = 0;
	for (i = 1; i <= 2 * m; i++)
	{
		x = a + (i - 0.5) * h;
		s += f(x) * h;
	}
	return s;
}

double trapezoidal(double a, double b, int m)
{
	int i;
	//length of subintervals
	double h = (b - a) / (2 * m);
	double x, s = 0;
	for (i = 1; i < 2 * m; i++)
	{
		x = a + i * h;
		s += f(x);
	}
	return h / 2 * (f(a) + f(b) + 2 * s);
}

double simpson(double a, double b, int m)
{
	int i;
	//length of subintervals
	double h = (b - a) / (2 * m);
	double x, s0, s1;
	s0 = 0;
	s1 = 0;
	for (i = 1; i < 2 * m; i++)
	{
		x = a + i * h;
		if (i % 2 == 0)
		{
			s0 += f(x);
		}
		else
		{
			s1 += f(x);
		}
	}
	return h / 3 * (f(a) + f(b) + 2 * s0 + 4 * s1);
}

void error(int code)
{
	switch (code)
	{
	case 1:
		printf("memory allocation error\n");
		exit(1);
	case 2:
		printf("file opening error\n");
		exit(2);
	case 3:
		printf("invalid calculations\n");
		exit(4);
	}
}
