cmd_lib/842/built-in.a := rm -f lib/842/built-in.a;  printf "lib/842/%s " 842_compress.o 842_decompress.o | xargs ar cDPrST lib/842/built-in.a
