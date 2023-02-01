cmd_lib/xz/built-in.a := rm -f lib/xz/built-in.a;  printf "lib/xz/%s " xz_dec_syms.o xz_dec_stream.o xz_dec_lzma2.o | xargs ar cDPrST lib/xz/built-in.a
