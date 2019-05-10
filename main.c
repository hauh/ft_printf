#include "srcs/ft_printf.h"
#include <stdio.h>

int main(void)
{
	double p = 373.85;
	int n;
//	wchar_t c1 = L'Ж';
//	wchar_t c2 = L'Œ';

	ft_printf(">%#+30.g<\n", 10000.03);
	printf(">%#+30.g<\n", 10000.03);
	ft_printf(">%#+-030.g<\n", 10000.03);
	printf(">%#+-030.g<\n", 10000.03);
//	ft_printf("%-05C<\n", c2);

}