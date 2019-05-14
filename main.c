#include "srcs/ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>

int main(void)
{
	int n = 12345678;
	int j = 0;
//	ft_printf(">%#.1000b<\n>%10-#b<\n>%10-#b<\n>%10-b<\n>%10.5-b<\n>%10.5-b<\n>%12.8#b<\n>%12.8#b<\n>%10-b<\n>%10-b<\n", 0, 2, 3, 5, 8, 12, 16, 22, 99, 18446744073709551615);
//	printf(">%#.1000x<\n", 0);

	while (j < 2000000000)
	{
		n *= -1;
		j++;
	}
}