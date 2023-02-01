cmd_fs/exportfs/built-in.a := rm -f fs/exportfs/built-in.a;  printf "fs/exportfs/%s " expfs.o | xargs ar cDPrST fs/exportfs/built-in.a
