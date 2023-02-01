cmd_fs/affs/affs.mod := printf '%s\n'   super.o namei.o inode.o file.o dir.o amigaffs.o bitmap.o symlink.o | awk '!x[$$0]++ { print("fs/affs/"$$0) }' > fs/affs/affs.mod
