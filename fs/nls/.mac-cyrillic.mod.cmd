cmd_fs/nls/mac-cyrillic.mod := printf '%s\n'   mac-cyrillic.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/mac-cyrillic.mod
