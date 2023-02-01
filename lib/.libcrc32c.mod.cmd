cmd_lib/libcrc32c.mod := printf '%s\n'   libcrc32c.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/libcrc32c.mod
