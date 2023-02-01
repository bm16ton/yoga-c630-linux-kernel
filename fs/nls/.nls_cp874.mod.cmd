cmd_fs/nls/nls_cp874.mod := printf '%s\n'   nls_cp874.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/nls_cp874.mod
