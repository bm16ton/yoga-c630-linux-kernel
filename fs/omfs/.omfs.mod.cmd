cmd_fs/omfs/omfs.mod := printf '%s\n'   bitmap.o dir.o file.o inode.o | awk '!x[$$0]++ { print("fs/omfs/"$$0) }' > fs/omfs/omfs.mod
