cmd_lib/zlib_deflate/built-in.a := rm -f lib/zlib_deflate/built-in.a;  printf "lib/zlib_deflate/%s " deflate.o deftree.o deflate_syms.o | xargs ar cDPrST lib/zlib_deflate/built-in.a
