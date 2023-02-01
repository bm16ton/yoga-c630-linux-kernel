cmd_fs/autofs/autofs4.mod := printf '%s\n'   init.o inode.o root.o symlink.o waitq.o expire.o dev-ioctl.o | awk '!x[$$0]++ { print("fs/autofs/"$$0) }' > fs/autofs/autofs4.mod
