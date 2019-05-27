#include "ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>

int main()
{
	long double n = 3.2;
	long double i = INFINITY;
	long double z = 0.;

	double l1 = 8008.2;
	double l2 = 7777.477;
	double ll1 = 1703.0541684;
	double ll2 = 1.01;
	double c1 = 42.42;
	double c2 = 54321.12345;

		ft_printf("%- 15.5hha\n", c1);
		printf("%- 15.5hha\n", c1);

}