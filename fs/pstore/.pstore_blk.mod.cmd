cmd_fs/pstore/pstore_blk.mod := printf '%s\n'   blk.o | awk '!x[$$0]++ { print("fs/pstore/"$$0) }' > fs/pstore/pstore_blk.mod
