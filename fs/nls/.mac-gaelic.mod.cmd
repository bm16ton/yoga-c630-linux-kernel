cmd_fs/nls/mac-gaelic.mod := printf '%s\n'   mac-gaelic.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/mac-gaelic.mod
