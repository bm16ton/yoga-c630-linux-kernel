cmd_fs/nls/mac-inuit.mod := printf '%s\n'   mac-inuit.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/mac-inuit.mod
