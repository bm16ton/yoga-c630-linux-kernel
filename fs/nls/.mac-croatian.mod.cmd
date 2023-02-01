cmd_fs/nls/mac-croatian.mod := printf '%s\n'   mac-croatian.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/mac-croatian.mod
