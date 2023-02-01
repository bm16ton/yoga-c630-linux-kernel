cmd_fs/overlayfs/overlay.mod := printf '%s\n'   super.o namei.o util.o inode.o file.o dir.o readdir.o copy_up.o export.o | awk '!x[$$0]++ { print("fs/overlayfs/"$$0) }' > fs/overlayfs/overlay.mod
