cmd_lib/crc-itu-t.mod := printf '%s\n'   crc-itu-t.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/crc-itu-t.mod
