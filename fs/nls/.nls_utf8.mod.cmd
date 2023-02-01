cmd_fs/nls/nls_utf8.mod := printf '%s\n'   nls_utf8.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/nls_utf8.mod
