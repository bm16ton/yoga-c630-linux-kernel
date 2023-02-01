cmd_fs/nls/nls_ascii.mod := printf '%s\n'   nls_ascii.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/nls_ascii.mod
