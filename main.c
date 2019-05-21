#include "srcs/ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>

void power_of_two(char *power, int pwr)
{
	int n;
	int m;

	while (pwr)
	{
		n = 5000;
		while (n)
		{
			power[n] *= 2;
			--n;
		}
		n = 5000;
		while (n)
		{
			if (power[n] > 9)
			{
				power[n] -= 10;
				++power[n - 1];
			}
			--n;
		}
		--pwr;
	}
}

void add_power(char *summ, int pwr)
{
	char power[5002];
	int n;

	power[5001] = 0;
	n = 5000;
	ft_memset(power, 0, n);
	power[n] = 1;
	power_of_two(&power[0], pwr);
	while (n)
	{
		summ[n] += power[n];
		--n;
	}
	n = 5000;
	while (n)
	{
		if (summ[n] > 9)
		{
			summ[n] -= 10;
			++summ[n - 1];
		}
		--n;
	}
}

void summ_powers(void)
{
	char summ[5002];
	int n;
	int m;

	summ[5001] = 0;
	n = 5000;
	ft_memset(summ, 0, n + 1);

	add_power(&summ[0], 2);
	add_power(&summ[0], 4);
	add_power(&summ[0], 4);
	add_power(&summ[0], 10);

	n = 0;
	while (!summ[n])
		++n;
	m = n;
	while (n <= 5000)
	{
		summ[n] += '0';
		++n;
	}
	ft_printf("%s\n", &summ[m]);
}

int main(void)
{
	long double t = 987654322234233.123123188823123123L;
	double p = 987654322234233.123123188823123123L;

//	printf(">%-+60.50Le<\n", -t);
//	ft_printf(">%-+60.50Le<\n", -t);
//	printf(">%-+60.50e<\n", -p);
//	ft_printf(">%-+60.50e<\n", -p);

	summ_powers();
}