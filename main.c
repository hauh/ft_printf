#include "srcs/ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>

int main(void)
{
	int c = 1500;
	int i;

	i = printf("%lc", c);
	ft_printf(" %d", i);
}
