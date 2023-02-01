cmd_fs/bfs/bfs.mod := printf '%s\n'   inode.o file.o dir.o | awk '!x[$$0]++ { print("fs/bfs/"$$0) }' > fs/bfs/bfs.mod
