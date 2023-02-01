cmd_lib/ts_bm.mod := printf '%s\n'   ts_bm.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/ts_bm.mod
