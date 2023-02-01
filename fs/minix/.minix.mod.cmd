cmd_fs/minix/minix.mod := printf '%s\n'   bitmap.o itree_v1.o itree_v2.o namei.o inode.o file.o dir.o | awk '!x[$$0]++ { print("fs/minix/"$$0) }' > fs/minix/minix.mod
