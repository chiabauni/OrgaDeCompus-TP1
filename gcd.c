#include <stddef.h>
#include <assert.h>
#include "gcd.h"

#define MAX(x, y) ((x) >= (y) ? (x) : (y))
#define MIN(x, y) ((x) <= (y) ? (x) : (y))

static int euclides_(int, int);

void
euclides(struct gcd *gcd, size_t n)
{
	size_t k;

#define ABS(x) \
	((x) < 0 ? -(x) : (x))

	for (k = 0; k < n; ++k)
       		gcd[k].gcd_ab = euclides_(ABS(gcd[k].num_a), 
		                          ABS(gcd[k].num_b));
}

static int
euclides_(int a, int b)
{
	int r2 = MAX(a, b);
	int r1 = MIN(a, b);
	int r0;

	while (1) {	
		if ((r0 = r2 % r1) == 0)
			break;
		r2 = r1;
		r1 = r0;
	}

	return r1;
}
