cmd_fs/mbcache.mod := printf '%s\n'   mbcache.o | awk '!x[$$0]++ { print("fs/"$$0) }' > fs/mbcache.mod
