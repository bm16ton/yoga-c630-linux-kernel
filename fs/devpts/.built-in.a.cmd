cmd_fs/devpts/built-in.a := rm -f fs/devpts/built-in.a;  printf "fs/devpts/%s " inode.o | xargs ar cDPrST fs/devpts/built-in.a
