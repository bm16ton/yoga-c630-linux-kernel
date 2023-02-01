cmd_arch/arm64/lib/built-in.a := rm -f arch/arm64/lib/built-in.a;  printf "arch/arm64/lib/%s " crc32.o error-inject.o mte.o | xargs ar cDPrST arch/arm64/lib/built-in.a
