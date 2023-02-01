cmd_fs/nls/mac-celtic.mod := printf '%s\n'   mac-celtic.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/mac-celtic.mod
