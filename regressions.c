#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#include "gcd.h"

#define SZ(x) \
	(sizeof(x) / sizeof((x)[0]))

#define REGRESSION(x, y, z)      \
	{ (x), (y), (z) },       \
	{ (y), (z), (z) },       \
	{ -(x), (y), (z) },      \
	{ -(y), -(x), (z) },     \
	{ (x), -(y), (z) },      \
	{ -(y), (x), (z) },      \
	{ -(x), -(y), (z) },     \
	{ -(y), -(x), (z) },     \
	{ 13*(x), (y), (z) },    \
	{ (x), 13*(y), (z) },    \
	{ 2*(x), 2*(y), 2*(z) }, \
	{ 3*(x), 3*(y), 3*(z) }

int
main(int argc, char * const argv[])
{
	struct gcd ref[] = {
		REGRESSION(1, 1, 1),
		REGRESSION(7, 1, 1),
		REGRESSION(13, 13, 13),
		REGRESSION(100, 10, 10),
		REGRESSION(100, 60, 20),
		REGRESSION(50, 75, 25),
	};
	struct gcd io[SZ(ref)];
	size_t k;

	for (k = 0; k < SZ(ref); k++) {
		io[k].num_a = ref[k].num_a;
		io[k].num_b = ref[k].num_b;
		io[k].gcd_ab = -1;
	}

	euclides(io, SZ(ref));

	for (k = 0; k < SZ(ref); k++) {
#if 0
		printf("GCD(%d, %d) = %d\n", 
		       io[k].num_a, 
		       io[k].num_b, 
		       io[k].gcd_ab);
#endif
		assert(io[k].gcd_ab == ref[k].gcd_ab);
	}

	return 0;
}
