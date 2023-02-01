cmd_lib/crc7.mod := printf '%s\n'   crc7.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/crc7.mod
