#include "srcs/ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>

int main(void)
{
	float d = 0.0/0.0;

	ft_printf("{%.100s}", "asdadsfasdfsad");
	printf("{%.100s}", "asdadsfasdfsad");
//	printf(">%.20F<\n", d);
}
