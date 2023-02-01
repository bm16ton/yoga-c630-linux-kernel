cmd_fs/nls/nls_cp852.mod := printf '%s\n'   nls_cp852.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/nls_cp852.mod
