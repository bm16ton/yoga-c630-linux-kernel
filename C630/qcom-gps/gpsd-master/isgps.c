/*****************************************************************************

This is a decoder for the unnamed protocol described in IS-GPS-200,
the Navstar GPS Interface Specification, and used as a transport layer
for both GPS satellite downlink transmissions and the RTCM104 version 2
format for broadcasting differential-GPS corrections.

The purpose of this protocol is to support analyzing a serial bit
stream without byte framing into parity-checked 30-bit words.
Interpretation of the words is left to an upper layer. Note that
RTCM104 version 3 does *not* use this code; it assumes a byte-oriented
underlayer.

The upper layer must supply a preamble_match() hook to tell our
decoder when it has a legitimate start of packet, and a length_check()
hook to tell it when the packet has reached the length it is supposed
to have.

This decoder is overkill as GNSS receivers already find the preamble
and word boundaries of the bitstream.

Here are Wolfgang's original rather cryptic notes on this code:

--------------------------------------------------------------------------
1) trim and bitflip the input.

While syncing the msb of the input gets shifted into lsb of the
assembled word.
    word <<= 1, or in input >> 5
    word <<= 1, or in input >> 4
    word <<= 1, or in input >> 3
    word <<= 1, or in input >> 2
    word <<= 1, or in input >> 1
    word <<= 1, or in input

At one point it should sync-lock.

----

Shift 6 bytes of RTCM data in as such:

---> (trim-bits-to-5-bits) ---> (end-for-end-bit-flip) --->

---> shift-into-30-bit-shift-register
              |||||||||||||||||||||||
	      detector-for-preamble
              |||||||||||||||||||||||
              detector-for-parity
              |||||||||||||||||||||||
--------------------------------------------------------------------------

The code was originally by Wolfgang Rupprecht.  ESR severely hacked
it, with Wolfgang's help, in order to separate message analysis from
message dumping and separate this lower layer from the upper layer
handing GPS-subframe and RTCM decoding.

You are not expected to understand any of this.

This file is Copyright (c) 2010-2018 by the GPSD project
SPDX-License-Identifier: BSD-2-clause

*****************************************************************************/

#include "gpsd_config.h"  /* must be before all includes */

#include <stdbool.h>
#include "gpsd.h"

#define MAG_SHIFT 6u
#define MAG_TAG_DATA (1 << MAG_SHIFT)
#define MAG_TAG_MASK (3 << MAG_SHIFT)

#define W_DATA_MASK	0x3fffffc0u

static unsigned char parity_array[] = {
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0
};

static unsigned int reverse_bits[] = {
    0, 32, 16, 48, 8, 40, 24, 56, 4, 36, 20, 52, 12, 44, 28, 60,
    2, 34, 18, 50, 10, 42, 26, 58, 6, 38, 22, 54, 14, 46, 30, 62,
    1, 33, 17, 49, 9, 41, 25, 57, 5, 37, 21, 53, 13, 45, 29, 61,
    3, 35, 19, 51, 11, 43, 27, 59, 7, 39, 23, 55, 15, 47, 31, 63
};


unsigned int isgps_parity(isgps30bits_t th)
{
#define P_30_MASK	0x40000000u

#define	PARITY_25	0xbb1f3480u
#define	PARITY_26	0x5d8f9a40u
#define	PARITY_27	0xaec7cd00u
#define	PARITY_28	0x5763e680u
#define	PARITY_29	0x6bb1f340u
#define	PARITY_30	0x8b7a89c0u
    isgps30bits_t t;
    unsigned int p;

    /*
     * if (th & P_30_MASK)
     * th ^= W_DATA_MASK;
     */

    t = th & PARITY_25;
    p = parity_array[t & 0xff] ^ parity_array[(t >> 8) & 0xff] ^
	parity_array[(t >> 16) & 0xff] ^ parity_array[(t >> 24) & 0xff];
    t = th & PARITY_26;
    p = (p << 1) | (parity_array[t & 0xff] ^ parity_array[(t >> 8) & 0xff] ^
		    parity_array[(t >> 16) & 0xff] ^ parity_array[(t >> 24) &
								  0xff]);
    t = th & PARITY_27;
    p = (p << 1) | (parity_array[t & 0xff] ^ parity_array[(t >> 8) & 0xff] ^
		    parity_array[(t >> 16) & 0xff] ^ parity_array[(t >> 24) &
								  0xff]);
    t = th & PARITY_28;
    p = (p << 1) | (parity_array[t & 0xff] ^ parity_array[(t >> 8) & 0xff] ^
		    parity_array[(t >> 16) & 0xff] ^ parity_array[(t >> 24) &
								  0xff]);
    t = th & PARITY_29;
    p = (p << 1) | (parity_array[t & 0xff] ^ parity_array[(t >> 8) & 0xff] ^
		    parity_array[(t >> 16) & 0xff] ^ parity_array[(t >> 24) &
								  0xff]);
    t = th & PARITY_30;
    p = (p << 1) | (parity_array[t & 0xff] ^ parity_array[(t >> 8) & 0xff] ^
		    parity_array[(t >> 16) & 0xff] ^ parity_array[(t >> 24) &
								  0xff]);

#ifdef __UNUSED__
    GPSD_LOG(ISGPS_ERRLEVEL_BASE + 2, errout, "ISGPS parity %u\n", p);
#endif /* __UNUSED__ */
    return (p);
}

/*
 * ESR found a doozy of a bug...
 *
 * Defining isgps_parityok as a function triggers an optimizer bug in gcc
 * 3.4.2. The symptom is that parity computation is screwed up and the decoder
 * never achieves sync lock.  Something steps on the argument to
 * isgpsparity(); the lossage appears to be related to the compiler's
 * attempt to fold the isgps_parity() call into isgps_parityok() in some
 * tail-recursion-like manner.  This happens under -O2, but not -O1, on
 * both i386 and amd64.  Disabling all of the individual -O2 suboptions
 * does *not* fix it.
 *
 * And the fun doesn't stop there! It turns out that even with this fix, bare
 * -O2 generates bad code.  It takes "-O2 -fschedule-insns" to generate good
 * code under 3.4.[23]...which is weird because -O2 is supposed to *imply*
 * -fschedule-insns.
 *
 *  gcc 4.0 does not manifest these bugs.
 */
#define isgps_parityok(w)	(isgps_parity(w) == ((w) & 0x3f))

void isgps_init(struct gps_lexer_t *lexer)
{
    lexer->isgps.curr_word = 0;
    lexer->isgps.curr_offset = 24;	/* first word */
    lexer->isgps.locked = false;
    lexer->isgps.bufindex = 0;
    lexer->isgps.buflen = 0;
}

// This works around cppcheck not looking into enough config branches
// cppcheck-suppress unusedFunction
enum isgpsstat_t isgps_decode(struct gps_lexer_t *lexer,
			      bool(*preamble_match) (isgps30bits_t *),
			      bool(*length_check) (struct gps_lexer_t *),
			      size_t maxlen, unsigned int c)
{
    /* ASCII characters 64-127, @ through DEL */
    if ((c & MAG_TAG_MASK) != MAG_TAG_DATA) {
	GPSD_LOG(ISGPS_ERRLEVEL_BASE + 1, &lexer->errout,
		 "ISGPS word tag not correct, skipping byte\n");
	return ISGPS_SKIP;
    }

    c = reverse_bits[c & 0x3f];

    if (!lexer->isgps.locked) {
	lexer->isgps.curr_offset = -5;
	lexer->isgps.bufindex = 0;

	while (lexer->isgps.curr_offset <= 0) {
	    lexer->isgps.curr_word <<= 1;
	    if (lexer->isgps.curr_offset > 0) {
		lexer->isgps.curr_word |= c << lexer->isgps.curr_offset;
	    } else {
		lexer->isgps.curr_word |=
		    c >> -(lexer->isgps.curr_offset);
	    }
	    GPSD_LOG(ISGPS_ERRLEVEL_BASE + 2, &lexer->errout,
		     "ISGPS syncing at byte %lu: 0x%08x\n",
		     lexer->char_counter, lexer->isgps.curr_word);

	    if (preamble_match(&lexer->isgps.curr_word)) {
		if (isgps_parityok(lexer->isgps.curr_word)) {
		    GPSD_LOG(ISGPS_ERRLEVEL_BASE + 1, &lexer->errout,
			     "ISGPS preamble ok, parity ok -- locked\n");
		    lexer->isgps.locked = true;
		    break;
		}
		GPSD_LOG(ISGPS_ERRLEVEL_BASE + 1, &lexer->errout,
			 "ISGPS preamble ok, parity fail\n");
	    }
	    lexer->isgps.curr_offset++;
	}			/* end while */
    }
    if (lexer->isgps.locked) {
	enum isgpsstat_t res;

	res = ISGPS_SYNC;

	if (lexer->isgps.curr_offset > 0) {
	    lexer->isgps.curr_word |= c << lexer->isgps.curr_offset;
	} else {
	    lexer->isgps.curr_word |= c >> -(lexer->isgps.curr_offset);
	}

	if (lexer->isgps.curr_offset <= 0) {
	    /* weird-assed inversion */
	    if (lexer->isgps.curr_word & P_30_MASK)
		lexer->isgps.curr_word ^= W_DATA_MASK;

	    if (isgps_parityok(lexer->isgps.curr_word)) {
#if 0
		/*
		 * Don't clobber the buffer just because we spot
		 * another preamble pattern in the data stream. -wsr
		 */
		if (preamble_match(&lexer->isgps.curr_word)) {
		    GPSD_LOG(ISGPS_ERRLEVEL_BASE + 2, &lexer->errout,
			     "ISGPS preamble spotted (index: %u)\n",
			     lexer->isgps.bufindex);
		    lexer->isgps.bufindex = 0;
		}
#endif
		GPSD_LOG(ISGPS_ERRLEVEL_BASE + 2, &lexer->errout,
			 "ISGPS processing word %u (offset %d)\n",
			 lexer->isgps.bufindex,
			 lexer->isgps.curr_offset);
		{
		    /*
		     * Guard against a buffer overflow attack.  Just wait for
		     * the next preamble match and go on from there.
		     */
		    if (lexer->isgps.bufindex >= (unsigned)maxlen) {
			lexer->isgps.bufindex = 0;
			GPSD_LOG(ISGPS_ERRLEVEL_BASE + 1, &lexer->errout,
				 "ISGPS buffer overflowing -- resetting\n");
			return ISGPS_NO_SYNC;
		    }

		    lexer->isgps.buf[lexer->isgps.bufindex] =
			lexer->isgps.curr_word;

		    /* *INDENT-OFF* */
		    if ((lexer->isgps.bufindex == 0) &&
			!preamble_match((isgps30bits_t *) lexer->isgps.buf)) {
			GPSD_LOG(ISGPS_ERRLEVEL_BASE + 1, &lexer->errout,
				 "ISGPS word 0 not a preamble- punting\n");
			return ISGPS_NO_SYNC;
		    }
		    /* *INDENT-ON* */
		    lexer->isgps.bufindex++;

		    if (length_check(lexer)) {
			/* jackpot, we have a complete packet */
			lexer->isgps.buflen = lexer->isgps.bufindex * sizeof(isgps30bits_t);
			lexer->isgps.bufindex = 0;
			res = ISGPS_MESSAGE;
		    }
		}
		lexer->isgps.curr_word <<= 30;	/* preserve the 2 low bits */
		lexer->isgps.curr_offset += 30;
		if (lexer->isgps.curr_offset > 0) {
		    lexer->isgps.curr_word |=
			c << lexer->isgps.curr_offset;
		} else {
		    lexer->isgps.curr_word |=
			c >> -(lexer->isgps.curr_offset);
		}
	    } else {
		GPSD_LOG(ISGPS_ERRLEVEL_BASE, &lexer->errout,
			 "ISGPS parity failure, lost lock\n");
		lexer->isgps.locked = false;
	    }
	}
	lexer->isgps.curr_offset -= 6;
	GPSD_LOG(ISGPS_ERRLEVEL_BASE + 2, &lexer->errout,
		 "ISGPS residual %d\n",
		 lexer->isgps.curr_offset);
	return res;
    }

    /* never achieved lock */
    GPSD_LOG(ISGPS_ERRLEVEL_BASE + 1, &lexer->errout,
	     "ISGPS lock never achieved\n");
    return ISGPS_NO_SYNC;
}

