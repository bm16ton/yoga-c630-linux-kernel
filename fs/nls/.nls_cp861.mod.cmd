cmd_fs/nls/nls_cp861.mod := printf '%s\n'   nls_cp861.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/nls_cp861.mod
