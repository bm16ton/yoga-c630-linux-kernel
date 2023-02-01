cmd_fs/exfat/exfat.mod := printf '%s\n'   inode.o namei.o dir.o super.o fatent.o cache.o nls.o misc.o file.o balloc.o | awk '!x[$$0]++ { print("fs/exfat/"$$0) }' > fs/exfat/exfat.mod
