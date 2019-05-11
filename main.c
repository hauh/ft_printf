#include "srcs/ft_printf.h"
#include <stdio.h>
#include <wchar.h>

int main(void)
{
	double p = 373.85;
	int n;
	wchar_t c1 = L'Ж';
	wchar_t c2 = L'Œ';
	const wchar_t *r = L"我是一只猫。";


	ft_printf("{%*.*d}\n", -15, -10, 42);
	printf("{%*.*d}\n", -15, -10, 42);
	}