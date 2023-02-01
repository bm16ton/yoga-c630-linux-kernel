cmd_fs/fuse/cuse.mod := printf '%s\n'   cuse.o | awk '!x[$$0]++ { print("fs/fuse/"$$0) }' > fs/fuse/cuse.mod
