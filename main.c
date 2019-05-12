#include "srcs/ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>

int main(void)
{
	double p = 373.85;
	wchar_t c1 = L'Ж';
	wchar_t c2 = L'Œ';
	const wchar_t *r = L"我是一只猫。";
	double n = 0.2f;


	ft_printf(">%1.10g<\n", -10.00100);
	printf(">%1.10g<\n", -10.00100);
	}