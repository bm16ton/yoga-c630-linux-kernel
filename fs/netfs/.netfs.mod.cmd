cmd_fs/netfs/netfs.mod := printf '%s\n'   buffered_read.o io.o main.o objects.o stats.o | awk '!x[$$0]++ { print("fs/netfs/"$$0) }' > fs/netfs/netfs.mod
