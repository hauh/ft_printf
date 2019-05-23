#include "srcs/ft_printf.h"
#include <stdio.h>
#include <wchar.h>
#include <math.h>

static void comb(char *power, char *p_end)
{
	while (p_end >= power)
	{
		while (*p_end > 9)
		{
			*p_end -= 10;
			++(*(p_end - 1));
		}
		--p_end;
	}
}

void power_of_two(char *integ_end, int pwr)
{
	char *power;
	char *p;
	char *p_end;

	power = (char *)malloc(sizeof(char) * (pwr / 2 + 2));
	ft_bzero(power, pwr / 2 + 2);
	p_end = power + pwr / 2 + 1;
	*(power + pwr / 2) = 1;
	while (pwr)
	{
		p = power;
		while (p < p_end)
			*p++ *= 2;
		comb(power, p_end);
		--pwr;
	}
	p = integ_end;
	while (p_end-- >= power)
	{
		*p += *p_end;
		--p;
	}
	free(power);
	comb(p, integ_end);
}

void power_negative(char *fract, int pwr)
{
	char *power;
	char *p;
	char *p_end;

	pwr = ~pwr + 1;
	power = (char *)malloc(sizeof(char) * (pwr + 1));
	ft_bzero(power, pwr + 1);
	p_end = power + pwr;
	*(power + pwr - 1) = 1;
	while (pwr)
	{
		p = power;
		while (p < p_end)
			*p++ *= 5;
		comb(power, p_end);
		--pwr;
	}
	p = power;
	while (p < p_end)
	{
		*fract += *p;
		++p;
		++fract;
	}
	comb(fract - (p - power), fract);
//	free(power);
}

int main(void)
{
	char *integ;
	char *fract;
	char *p;
	char *integ_end;
	char *fract_end;
	t_bits nn;
	t_ld nbr;
	int n;
	int m;
	int prec = 32;

	nn.l = -0.00000000003456;
	nbr.exponent = nn.lsh[4] - 16383;
	nbr.mantissa = *(unsigned long long *)&nn.l;
	nbr.sign = nn.lsh[4] >> 15;

	int bl = 64;

	integ = NULL;
	fract = NULL;
	if (nbr.exponent > 0)
	{
		integ = (char *)malloc(sizeof(char) * (nbr.exponent + 1));
		ft_bzero(integ, nbr.exponent + 2);
		integ_end = integ + nbr.exponent;
	}
	if (63 - nbr.exponent > 0)
	{
		fract = (char *)malloc(sizeof(char) * (64 - nbr.exponent));
		ft_bzero(fract, 64 - nbr.exponent);
		fract_end = fract + 63 - nbr.exponent;
	}
	while (bl-- > 0)
	{
		if (nbr.mantissa & (1L << bl))
			nbr.exponent >= 0 ? power_of_two(integ_end, nbr.exponent) : power_negative(fract, nbr.exponent);
		nbr.exponent--;
	}
	if (nbr.sign)
		printf("-");
	if (integ)
	{
		p = integ;
		while (!*p)
			++p;
		while (integ_end >= p)
			*integ_end-- += '0';
		printf("%s", integ_end + 1);
	}
	else
		printf("0");
	if (fract)
	{
		p = fract;
		while (p < fract_end)
			*p++ += '0';
		printf(".%s\n", fract);
	}
	else
		printf(".000000");
	printf("%.100Lf\n", nn.l);
}