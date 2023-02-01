cmd_fs/nls/mac-iceland.mod := printf '%s\n'   mac-iceland.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/mac-iceland.mod
