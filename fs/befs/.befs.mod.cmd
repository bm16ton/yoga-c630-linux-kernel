cmd_fs/befs/befs.mod := printf '%s\n'   datastream.o btree.o super.o inode.o debug.o io.o linuxvfs.o | awk '!x[$$0]++ { print("fs/befs/"$$0) }' > fs/befs/befs.mod
