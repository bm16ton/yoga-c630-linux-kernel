cmd_fs/sysv/sysv.mod := printf '%s\n'   ialloc.o balloc.o inode.o itree.o file.o dir.o namei.o super.o | awk '!x[$$0]++ { print("fs/sysv/"$$0) }' > fs/sysv/sysv.mod
