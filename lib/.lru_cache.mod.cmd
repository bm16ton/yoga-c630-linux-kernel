cmd_lib/lru_cache.mod := printf '%s\n'   lru_cache.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/lru_cache.mod
