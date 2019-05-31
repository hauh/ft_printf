#include "ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>

int main()
{
	char	*str;
    int     c = 0xd800;

    str = "bla";
	ft_printf("{%f}{%F}\n", 1.42, 1.42);
	printf("{%f}{%F}\n", 1.42, 1.42);
}