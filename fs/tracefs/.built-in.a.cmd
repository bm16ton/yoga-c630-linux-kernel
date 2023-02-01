cmd_fs/tracefs/built-in.a := rm -f fs/tracefs/built-in.a;  printf "fs/tracefs/%s " inode.o | xargs ar cDPrST fs/tracefs/built-in.a
