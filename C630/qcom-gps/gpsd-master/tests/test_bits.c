/* test harness for bits.h
 *
 * This file is Copyright (c) 2010 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "../bits.h"

static unsigned char buf[80];
static signed char sb1, sb2;
static unsigned char ub1, ub2;
static short sw1, sw2;
static unsigned short uw1, uw2;
static int sl1, sl2;
static unsigned int ul1, ul2;
static int64_t sL1, sL2;
static uint64_t uL1, uL2;
static float f1;
static double d1;

static char *hexdump(const void *binbuf, size_t len)
{
    static char hexbuf[BUFSIZ];
    size_t i, j = 0;
    const char *ibuf = (const char *)binbuf;
    const char *hexchar = "0123456789abcdef";

    for (i = 0; i < len; i++) {
	hexbuf[j++] = hexchar[(ibuf[i] & 0xf0) >> 4];
	hexbuf[j++] = hexchar[ibuf[i] & 0x0f];
    }
    hexbuf[j] = '\0';
    return hexbuf;
}

static void bedumpall(void)
{
    (void)printf("getsb: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) sb1, (uint64_t) sb2,
		 (uint64_t) getsb(buf, 0), (uint64_t) getsb(buf, 8));
    (void)printf("getub: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) ub1, (uint64_t) ub2,
		 (uint64_t) getub(buf, 0), (uint64_t) getub(buf, 8));
    (void)printf("getbes16: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) sw1, (uint64_t) sw2,
		 (uint64_t) getbes16(buf, 0), (uint64_t) getbes16(buf, 8));
    (void)printf("getbeu16: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) uw1, (uint64_t) uw2,
		 (uint64_t) getbeu16(buf, 0), (uint64_t) getbeu16(buf, 8));
    (void)printf("getbes32: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) sl1, (uint64_t) sl2,
		 (uint64_t) getbes32(buf, 0), (uint64_t) getbes32(buf, 8));
    (void)printf("getbeu32: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) ul1, (uint64_t) ul2,
		 (uint64_t) getbeu32(buf, 0), (uint64_t) getbeu32(buf, 8));
    (void)printf("getbes64: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) sL1, (uint64_t) sL2,
		 (uint64_t) getbes64(buf, 0), (uint64_t) getbes64(buf, 8));
    (void)printf("getbeu64: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) uL1, (uint64_t) uL2,
		 (uint64_t) getbeu64(buf, 0), (uint64_t) getbeu64(buf, 8));
    (void)printf("getbef32: %f %f\n", f1, getbef32((const char *)buf, 24));
    (void)printf("getbed64: %.16f %.16f\n", d1, getbed64((const char *)buf, 16));
}

static void ledumpall(void)
{
    (void)printf("getsb: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) sb1, (uint64_t) sb2,
		 (uint64_t) getsb(buf, 0), (uint64_t) getsb(buf, 8));
    (void)printf("getub: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) ub1, (uint64_t) ub2,
		 (uint64_t) getub(buf, 0), (uint64_t) getub(buf, 8));
    (void)printf("getles16: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) sw1, (uint64_t) sw2,
		 (uint64_t) getles16(buf, 0), (uint64_t) getles16(buf, 8));
    (void)printf("getleu16: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) uw1, (uint64_t) uw2,
		 (uint64_t) getleu16(buf, 0), (uint64_t) getleu16(buf, 8));
    (void)printf("getles32: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) sl1, (uint64_t) sl2,
		 (uint64_t) getles32(buf, 0), (uint64_t) getles32(buf, 8));
    (void)printf("getleu32: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) ul1, (uint64_t) ul2,
		 (uint64_t) getleu32(buf, 0), (uint64_t) getleu32(buf, 8));
    (void)printf("getles64: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) sL1, (uint64_t) sL2,
		 (uint64_t) getles64(buf, 0), (uint64_t) getles64(buf, 8));
    (void)printf("getleu64: %016" PRIx64 " %016" PRIx64 " %016" PRIx64 " %016" PRIx64 "\n",
		 (uint64_t) uL1, (uint64_t) uL2,
		 (uint64_t) getleu64(buf, 0), (uint64_t) getleu64(buf, 8));
    (void)printf("getlef32: %f %f\n", f1, getlef32((const char *)buf, 24));
    (void)printf("getled64: %.16f %.16f\n", d1, getled64((const char *)buf, 16));
}

struct unsigned_test
{
    unsigned char *buf;
    unsigned int start, width;
    uint64_t expected;
    bool le;
    char *description;
};

int main(int argc, char *argv[])
{
    bool failures = false;
    bool quiet = (argc > 1) && (strcmp(argv[1], "--quiet") == 0);

    struct unsigned_test *up, unsigned_tests[] = {
	/* tests using the big buffer */
	{buf, 0,  1,  0,    false, "first bit of first byte"},
	{buf, 0,  8,  0x01, false, "first 8 bits"},
	{buf, 32, 7,  0x02, false, "first seven bits of fifth byte (0x05)"},
	{buf, 56, 12, 0x8f, false, "12 bits crossing 7th to 8th bytes (0x08ff)"},
	{buf, 78, 4,  0xb, false, "4 bits crossing 8th to 9th byte (0xfefd)"},
	{buf, 0,  1,  0,    true,  "first bit of first byte"},
	{buf, 0,  8,  0x80, true,  "first 8 bits"},
	{buf, 32, 7,  0x20, true, "first seven bits of fifth byte (0x05)"},
	{buf, 56, 12, 0xf10,true, "12 bits crossing 7th to 8th bytes (0x08ff)"},
	{buf, 78, 4,  0xd,  true, "4 bits crossing 8th to 9th byte (0xfefd)"},
	/* sporadic tests based on found bugs */
	{(unsigned char *)"\x19\x23\f6",
	 7, 2, 2, false, "2 bits crossing 1st to 2nd byte (0x1923)"},
    };

    memcpy(buf, "\x01\x02\x03\x04\x05\x06\x07\x08", 8);
    memcpy(buf + 8, "\xff\xfe\xfd\xfc\xfb\xfa\xf9\xf8", 8);
    memcpy(buf + 16, "\x40\x09\x21\xfb\x54\x44\x2d\x18", 8);
    memcpy(buf + 24, "\x40\x49\x0f\xdb", 4);

    if (!quiet)
	(void)printf("Testing bitfield extraction\n");

    sb1 = getsb(buf, 0);
    sb2 = getsb(buf, 8);
    ub1 = getub(buf, 0);
    ub2 = getub(buf, 8);

    if (!quiet) {
	unsigned char *sp;

	(void)fputs("Test data:", stdout);
	for (sp = buf; sp < buf + 28; sp++)
	    (void)printf(" %02x", *sp);
	(void)putc('\n', stdout);

	/* big-endian test */
	printf("Big-endian:\n");
	sw1 = getbes16(buf, 0);
	sw2 = getbes16(buf, 8);
	uw1 = getbeu16(buf, 0);
	uw2 = getbeu16(buf, 8);
	sl1 = getbes32(buf, 0);
	sl2 = getbes32(buf, 8);
	ul1 = getbeu32(buf, 0);
	ul2 = getbeu32(buf, 8);
	sL1 = getbes64(buf, 0);
	sL2 = getbes64(buf, 8);
	uL1 = getbeu64(buf, 0);
	uL2 = getbeu64(buf, 8);
	f1 = getbef32((const char *)buf, 24);
	d1 = getbed64((const char *)buf, 16);
	bedumpall();

	/* little-endian test */
	printf("Little-endian:\n");
	sw1 = getles16(buf, 0);
	sw2 = getles16(buf, 8);
	uw1 = getleu16(buf, 0);
	uw2 = getleu16(buf, 8);
	sl1 = getles32(buf, 0);
	sl2 = getles32(buf, 8);
	ul1 = getleu32(buf, 0);
	ul2 = getleu32(buf, 8);
	sL1 = getles64(buf, 0);
	sL2 = getles64(buf, 8);
	uL1 = getleu64(buf, 0);
	uL2 = getleu64(buf, 8);
	f1 = getlef32((const char *)buf, 24);
	d1 = getled64((const char *)buf, 16);
	ledumpall();
    }

    if (sb1 != 1)  printf("getsb(buf, 0) FAILED\n");
    if (sb2 != -1) printf("getsb(buf, 8) FAILED\n");
    if (ub1 != 1)  printf("getub(buf, 0) FAILED\n");
    if (ub2 != 0xff) printf("getub(buf, 8) FAILED\n");

    for (up = unsigned_tests;
	 up <
	 unsigned_tests + sizeof(unsigned_tests) / sizeof(unsigned_tests[0]);
	 up++) {
	uint64_t res = ubits((unsigned char *)buf, up->start, up->width, up->le);
	bool success = (res == up->expected);
	if (!success)
	    failures = true;
	if (!success || !quiet)
	    (void)printf("ubits(%s, %d, %d, %s) %s should be %" PRIx64 ", is %" PRIx64 ": %s\n",
			 hexdump(buf, strlen((char *)buf)),
			 up->start, up->width, up->le ? "true" : "false",
			 up->description, up->expected, res,
			 success ? "succeeded" : "FAILED");
    }


    shiftleft(buf, 28, 30);
    if (!quiet)
	printf("Left-shifted 30 bits: %s\n", hexdump(buf, 28));
    /*
     * After the 24-bit shift, the bit array loses its first three bytes:
     * 0x0405060708 = 00000100 00000101 00000110 00000111 00001000
     * By inspection, the results of the 6-bit shift are
     * 00000001 01000001 10000001 11000010 00
     */
#define LASSERT(n, v) if (buf[n] != v) printf("Expected buf[%d] to be %02x, was %02x\n", n, v, buf[n])
    LASSERT(0, 0x01);
    LASSERT(1, 0x41);
    LASSERT(2, 0x81);
    LASSERT(3, 0xc1);
#undef LASSERT


    exit(failures ? EXIT_FAILURE : EXIT_SUCCESS);

}

