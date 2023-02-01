cmd_fs/iomap/built-in.a := rm -f fs/iomap/built-in.a;  printf "fs/iomap/%s " trace.o iter.o buffered-io.o direct-io.o fiemap.o seek.o swapfile.o | xargs ar cDPrST fs/iomap/built-in.a
