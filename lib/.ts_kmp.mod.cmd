cmd_lib/ts_kmp.mod := printf '%s\n'   ts_kmp.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/ts_kmp.mod
