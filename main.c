#include "srcs/ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>

int main(void)
{
//	int n;
//	long double t = 123456789.123456789;
	double p = 1.01L;

	ft_printf("%+80Lf", p);
//	printf("%+80LF\n", p);
}
