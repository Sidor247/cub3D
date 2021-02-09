#include <stdio.h>
#include <math.h>

int		main(void)
{
	float	x;

	x = 2.999999;
	x = floorf(x);
	printf("%.30f\n", x);
	return (0);
}