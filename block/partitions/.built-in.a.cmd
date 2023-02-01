cmd_block/partitions/built-in.a := rm -f block/partitions/built-in.a;  printf "block/partitions/%s " core.o msdos.o efi.o karma.o | xargs ar cDPrST block/partitions/built-in.a
