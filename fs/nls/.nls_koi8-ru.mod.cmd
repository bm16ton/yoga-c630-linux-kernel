cmd_fs/nls/nls_koi8-ru.mod := printf '%s\n'   nls_koi8-ru.o | awk '!x[$$0]++ { print("fs/nls/"$$0) }' > fs/nls/nls_koi8-ru.mod
