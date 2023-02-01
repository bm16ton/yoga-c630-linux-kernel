cmd_fs/nls/mac-turkish.mod := printf '%s\n'   mac-turkish.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/mac-turkish.mod
