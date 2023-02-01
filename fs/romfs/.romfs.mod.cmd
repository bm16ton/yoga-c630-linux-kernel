cmd_fs/romfs/romfs.mod := printf '%s\n'   storage.o super.o | awk '!x[$$0]++ { print("fs/romfs/"$$0) }' > fs/romfs/romfs.mod
