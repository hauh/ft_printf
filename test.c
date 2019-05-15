#include "unistd.h"

int main(void)
{
	char *s = "äååææåå";

	while (*s)
	{
		write(1, s, 1);
		++s;
	}
}
