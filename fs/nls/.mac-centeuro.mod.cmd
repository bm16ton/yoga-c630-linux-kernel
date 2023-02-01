cmd_fs/nls/mac-centeuro.mod := printf '%s\n'   mac-centeuro.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/mac-centeuro.mod
