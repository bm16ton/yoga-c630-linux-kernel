cmd_fs/coda/coda.mod := printf '%s\n'   psdev.o cache.o cnode.o inode.o dir.o file.o upcall.o coda_linux.o symlink.o pioctl.o sysctl.o | awk '!x[$$0]++ { print("fs/coda/"$$0) }' > fs/coda/coda.mod
