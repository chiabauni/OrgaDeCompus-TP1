#ifndef _GCD_H_INCLUDED_
#define _GCD_H_INCLUDED_

#include <stddef.h>

struct gcd {
	int num_a;
	int num_b;
	int gcd_ab;
};

extern void euclides(struct gcd *, size_t);
#endif
