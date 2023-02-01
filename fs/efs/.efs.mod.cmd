cmd_fs/efs/efs.mod := printf '%s\n'   super.o inode.o namei.o dir.o file.o symlink.o | awk '!x[$$0]++ { print("fs/efs/"$$0) }' > fs/efs/efs.mod
