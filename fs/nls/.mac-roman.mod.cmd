cmd_fs/nls/mac-roman.mod := printf '%s\n'   mac-roman.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/mac-roman.mod
