cmd_fs/fuse/fuse.mod := printf '%s\n'   dev.o dir.o file.o inode.o control.o xattr.o acl.o readdir.o ioctl.o | awk '!x[$$0]++ { print("fs/fuse/"$$0) }' > fs/fuse/fuse.mod
