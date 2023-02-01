cmd_fs/fscache/fscache.mod := printf '%s\n'   cache.o cookie.o io.o main.o volume.o proc.o stats.o | awk '!x[$$0]++ { print("fs/fscache/"$$0) }' > fs/fscache/fscache.mod
