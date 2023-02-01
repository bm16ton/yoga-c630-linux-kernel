cmd_fs/qnx6/qnx6.mod := printf '%s\n'   inode.o dir.o namei.o super_mmi.o | awk '!x[$$0]++ { print("fs/qnx6/"$$0) }' > fs/qnx6/qnx6.mod
