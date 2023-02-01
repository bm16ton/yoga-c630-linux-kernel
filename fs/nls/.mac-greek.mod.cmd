cmd_fs/nls/mac-greek.mod := printf '%s\n'   mac-greek.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/mac-greek.mod
