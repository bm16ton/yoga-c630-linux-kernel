cmd_fs/nls/mac-romanian.mod := printf '%s\n'   mac-romanian.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/mac-romanian.mod
