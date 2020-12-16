/*
 * This file is Copyright (c) 2010 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */
#include <stdio.h>

/*
 * Copyright (c) 2006 Chris Kuethe <chris.kuethe@gmail.com>
 *
 * This file is Copyright (c)2005-2019 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */

/*
 * this simple program tests to see whether your system can do proper
 * single and double precision floating point. This is apparently Very
 * Hard To Do(tm) on embedded systems, judging by the number of broken
 * ARM toolchains I've seen... :(
 *
 * Added in 2015 by ESR: Test for C99 behavior on negative operand(s)
 * of %, that is the result should have the sign of the left operand.
 *
 * compile with: gcc -O -o test_float test_float.c
 *     (use whatever -O level you like)
 */

int main(void);
int test_single(void);
int test_double(void);
int test_modulo(void);

int main(void) {
    int i, j, k;

	if ((i = test_single()))
		printf("WARNING: Single-precision "
			"floating point math might be broken\n");

	if ((j = test_double()))
		printf("WARNING: Double-precision "
			"floating point math might be broken\n");

	if ((k = test_modulo()))
		printf("WARNING: Modular arithmetic is broken\n");

	i += j;
	i += k;
	if (i == 0)
		printf("floating point and modular math appears to work\n");
	return i;
}

int test_single(void) {
	static float f;
	static int i;
	static int e = 0;

	/* addition test */
	f = 1.0;
	for(i = 0; i < 10; i++)
		f += (1<<i);
	if (f != 1024.0) {
		printf("s1 ");
		e++;
	}

	/* subtraction test */
	f = 1024.0;
	for(i = 0; i < 10; i++)
		f -= (1<<i);
	if (f != 1.0) {
		printf("s2 ");
		e++;
	}

	/* multiplication test */
	f = 1.0;
	for(i = 1; i < 10; i++)
		f *= i;
	if (f != 362880.0) {
		printf("s3 ");
		e++;
	}

	/* division test */
	f = 362880.0;
	for(i = 1; i < 10; i++)
		f /= i;
	if (f != 1.0) {
		printf("s4 ");
		e++;
	}

	/* multiply-accumulate test */
	f = 0.5;
	for(i = 1; i < 1000000; i++) {
		f += 2.0;
		f *= 0.5;
	}
	if (f != 2.0) {
		printf("s5 ");
		e++;
	}

	/* divide-subtract test */
	f = 2.0;
	for(i = 1; i < 1000000; i++) {
		f /= 0.5;
		f -= 2.0;
	}
	if (f != 2.0) {
		printf("s6 ");
		e++;
	}

	/* add-multiply-subtract-divide test */
	f = 1000000.0;
	for(i = 1; i < 1000000; i++)
		f = ((((f + 1.5) * 0.5) - 1.25) / 0.5);
	if (f != 1.0) {
		printf("s7 ");
		e++;
	}

	/* multiply-add-divide-subtract test */
	f = 1.0;
	for(i = 1; i < 1000000; i++)
		f = ((((f * 5.0) + 3.0) / 2.0) - 3.0);
	if (f != 1.0)
		printf("s8 ");

	/* subtract-divide-add-multiply test */
	f = 8.0;
	for(i = 1; i < 1000000; i++)
		f = ((((f - 5.0) / 2.0) + 2.5) * 2.0);
	if (f != 8.0) {
		printf("s9 ");
		e++;
	}

	/* divide-subtract-multiply-add test */
	f = 42.0;
	for(i = 1; i < 1000000; i++)
		f = ((((f / 6.0) - 5.0) * 19.75 ) + 2.5);
	if (f != 42.0) {
		printf("s10 ");
		e++;
	}
	if (e) {
		printf("\n");
		return 1;
	}
	return 0;
}


int test_double(void) {
	static double f;
	static int i;
	static int e = 0;

	/* addition test */
	f = 1.0;
	for(i = 0; i < 10; i++)
		f += (1<<i);
	if (f != 1024.0) {
		printf("d1 ");
		e++;
	}

	/* subtraction test */
	f = 1024.0;
	for(i = 0; i < 10; i++)
		f -= (1<<i);
	if (f != 1.0) {
		printf("d2 ");
		e++;
	}

	/* multiplication test */
	f = 1.0;
	for(i = 1; i < 10; i++)
		f *= i;
	if (f != 362880.0) {
		printf("d3 ");
		e++;
	}

	/* division test */
	f = 362880.0;
	for(i = 1; i < 10; i++)
		f /= i;
	if (f != 1.0) {
		printf("d4 ");
		e++;
	}

	/* multiply-accumulate test */
	f = 0.5;
	for(i = 1; i < 1000000; i++) {
		f += 2.0;
		f *= 0.5;
	}
	if (f != 2.0) {
		printf("d5 ");
		e++;
	}

	/* divide-subtract test */
	f = 2.0;
	for(i = 1; i < 1000000; i++) {
		f /= 0.5;
		f -= 2.0;
	}
	if (f != 2.0) {
		printf("d6 ");
		e++;
	}

	/* add-multiply-subtract-divide test */
	f = 1000000.0;
	for(i = 1; i < 1000000; i++)
		f = ((((f + 1.5) * 0.5) - 1.25) / 0.5);
	if (f != 1.0) {
		printf("d7 ");
		e++;
	}

	/* multiply-add-divide-subtract test */
	f = 1.0;
	for(i = 1; i < 1000000; i++)
		f = ((((f * 5.0) + 3.0) / 2.0) - 3.0);
	if (f != 1.0)
		printf("d8 ");

	/* subtract-divide-add-multiply test */
	f = 8.0;
	for(i = 1; i < 1000000; i++)
		f = ((((f - 5.0) / 2.0) + 2.5) * 2.0);
	if (f != 8.0) {
		printf("d9 ");
		e++;
	}

	/* divide-subtract-multiply-add test */
	f = 42.0;
	for(i = 1; i < 1000000; i++)
		f = ((((f / 6.0) - 5.0) * 19.75 ) + 2.5);
	if (f != 42.0) {
		printf("d10 ");
		e++;
	}
	if (e) {
		printf("\n");
		return 1;
	}
	return 0;
}

int test_modulo(void) {
    static int e = 0;

    /* make sure that gcc does not optimize these away */
    volatile int a;
    volatile int b;

    a = -5;
    b = 2;
    //cppcheck-suppress knownConditionTrueFalse
    if (a % b != -1) {
	printf("m1 ");
	e++;
    }

    a = -5;
    b = -2;
    //cppcheck-suppress knownConditionTrueFalse
    if (a % b != -1) {
	printf("m2 ");
	e++;
    }

    a = 5;
    b = -2;
    //cppcheck-suppress knownConditionTrueFalse
    if (a % b != 1) {
	printf("m3 ");
	e++;
    }

    if (e) {
	printf("\n");
	return 1;
    }
    return 0;
}
