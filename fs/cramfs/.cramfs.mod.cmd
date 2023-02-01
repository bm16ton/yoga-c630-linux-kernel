cmd_fs/cramfs/cramfs.mod := printf '%s\n'   inode.o uncompress.o | awk '!x[$$0]++ { print("fs/cramfs/"$$0) }' > fs/cramfs/cramfs.mod
