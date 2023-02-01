cmd_fs/qnx4/qnx4.mod := printf '%s\n'   inode.o dir.o namei.o bitmap.o | awk '!x[$$0]++ { print("fs/qnx4/"$$0) }' > fs/qnx4/qnx4.mod
