cmd_fs/efivarfs/efivarfs.mod := printf '%s\n'   inode.o file.o super.o vars.o | awk '!x[$$0]++ { print("fs/efivarfs/"$$0) }' > fs/efivarfs/efivarfs.mod
