cmd_fs/pstore/pstore_zone.mod := printf '%s\n'   zone.o | awk '!x[$$0]++ { print("fs/pstore/"$$0) }' > fs/pstore/pstore_zone.mod
