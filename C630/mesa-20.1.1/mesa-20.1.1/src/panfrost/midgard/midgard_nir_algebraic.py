#
# Copyright (C) 2018 Alyssa Rosenzweig
#
# Copyright (C) 2016 Intel Corporation
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

import argparse
import sys
import math

a = 'a'
b = 'b'
c = 'c'

algebraic_late = [
    # ineg must be lowered late, but only for integers; floats will try to
    # have modifiers attached... hence why this has to be here rather than
    # a more standard lower_negate approach

    (('ineg', a), ('isub', 0, a)),

    # These two special-cases save space/an op than the actual csel op +
    # scheduler flexibility

    (('b32csel', a, 'b@32', 0), ('iand', a, b)),
    (('b32csel', a, 0, 'b@32'), ('iand', ('inot', a), b)),
]


# Midgard is able to type convert down by only one "step" per instruction; if
# NIR wants more than one step, we need to break up into multiple instructions

converts = []

for op in ('u2u', 'i2i', 'f2f', 'i2f', 'u2f', 'f2i', 'f2u'):
    srcsz_max = 64
    dstsz_max = 64
    # 8 bit float doesn't exist
    srcsz_min = 8 if op[0] != 'f' else 16
    dstsz_min = 8 if op[2] != 'f' else 16
    dstsz = dstsz_min
    # Iterate over all possible destination and source sizes
    while dstsz <= dstsz_max:
        srcsz = srcsz_min
        while srcsz <= srcsz_max:
            # Size converter lowering is only needed if src and dst sizes are
            # spaced by a factor > 2.
            # Type converter lowering is needed as soon as src_size != dst_size
            if srcsz != dstsz and ((srcsz * 2 != dstsz and srcsz != dstsz * 2) or op[0] != op[2]):
                cursz = srcsz
                rule = a
                # When converting down we first do the type conversion followed
                # by one or more size conversions. When converting up, we do
                # the type conversion at the end. This way we don't have to
                # deal with the fact that f2f8 doesn't exists.
                sizeconvop = op[0] + '2' + op[0] if srcsz < dstsz else op[2] + '2' + op[2]
                if srcsz > dstsz and op[0] != op[2]:
                    rule = (op + str(int(cursz)), rule)
                while cursz != dstsz:
                    cursz = cursz / 2 if dstsz < srcsz else cursz * 2
                    rule = (sizeconvop + str(int(cursz)), rule)
                if srcsz < dstsz and op[0] != op[2]:
                    rule = (op + str(int(cursz)), rule)
                converts += [((op + str(int(dstsz)), 'a@' + str(int(srcsz))), rule)]
            srcsz *= 2
        dstsz *= 2

# Midgard outputs fp32 for specials. The f2f32 will be folded in later.
SPECIAL = ['fexp2', 'flog2', 'fsin', 'fcos', 'frcp', 'frsq']

for op in SPECIAL:
        converts += [((op + '@16', a), ('f2f16', (op, ('f2f32', a))))]

# Midgard scales fsin/fcos arguments by pi.
# Pass must be run only once, after the main loop

scale_trig = [
        (('fsin', a), ('fsin', ('fdiv', a, math.pi))),
        (('fcos', a), ('fcos', ('fdiv', a, math.pi))),
]

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--import-path', required=True)
    args = parser.parse_args()
    sys.path.insert(0, args.import_path)
    run()


def run():
    import nir_algebraic  # pylint: disable=import-error

    print('#include "midgard_nir.h"')

    print(nir_algebraic.AlgebraicPass("midgard_nir_lower_algebraic_late",
                                      algebraic_late + converts).render())

    print(nir_algebraic.AlgebraicPass("midgard_nir_scale_trig",
                                      scale_trig).render())


if __name__ == '__main__':
    main()
