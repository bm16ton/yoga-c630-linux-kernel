cmd_fs/adfs/adfs.mod := printf '%s\n'   dir.o dir_f.o dir_fplus.o file.o inode.o map.o super.o | awk '!x[$$0]++ { print("fs/adfs/"$$0) }' > fs/adfs/adfs.mod
