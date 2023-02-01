cmd_fs/fat/fat.mod := printf '%s\n'   cache.o dir.o fatent.o file.o inode.o misc.o nfs.o | awk '!x[$$0]++ { print("fs/fat/"$$0) }' > fs/fat/fat.mod
