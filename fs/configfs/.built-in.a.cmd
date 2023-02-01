cmd_fs/configfs/built-in.a := rm -f fs/configfs/built-in.a;  printf "fs/configfs/%s " inode.o file.o dir.o symlink.o mount.o item.o | xargs ar cDPrST fs/configfs/built-in.a
