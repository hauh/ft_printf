#include "srcs/ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>

int main()
{
	long double n = 3.2;
	long double i = INFINITY;
	long double z = 0.;

//	ft_printf(">%-+#100.40Lg<\n", 11.0L);
//	printf(">%-+#100.40Lg<\n", 11.0L);
//	ft_printf(">%-+#100.5000Lf<\n", 1);
//	ft_printf(">%A<\n", 3.2);
//	printf(">%L.1000F<\n", 7.16L - 7.0L);
	ft_printf("%+.2La\n", -0.0L);
	printf("%+.2La\n", -0.0L);
}