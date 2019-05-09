#include "srcs/ft_printf.h"
#include <stdio.h>

int main(void)
{
	wchar_t c1 = L'Ж';
	wchar_t c2 = L'Œ';

	ft_printf("%C", L'≠');
//	ft_printf("%-05C<\n", c1);
//	ft_printf("%-05C<\n", c2);
}
