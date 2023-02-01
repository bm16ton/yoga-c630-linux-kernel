cmd_fs/ufs/ufs.mod := printf '%s\n'   balloc.o cylinder.o dir.o file.o ialloc.o inode.o namei.o super.o util.o | awk '!x[$$0]++ { print("fs/ufs/"$$0) }' > fs/ufs/ufs.mod
