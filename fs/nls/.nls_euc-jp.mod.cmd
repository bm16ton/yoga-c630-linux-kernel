cmd_fs/nls/nls_euc-jp.mod := printf '%s\n'   nls_euc-jp.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/nls_euc-jp.mod
