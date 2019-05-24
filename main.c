#include "srcs/ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>

int main()
{
	long double n = -0.234562345;
	long double i = INFINITY;
	long double z = 0.;

	ft_printf(">%-+#100.40Lg<\n", 1);
	printf(">%-+#100.40Lg<\n", 1);
}