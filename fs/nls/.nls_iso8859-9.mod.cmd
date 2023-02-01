cmd_fs/nls/nls_iso8859-9.mod := printf '%s\n'   nls_iso8859-9.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/nls_iso8859-9.mod
