cmd_fs/pstore/ramoops.mod := printf '%s\n'   ram.o ram_core.o | awk '!x[$$0]++ { print("fs/pstore/"$$0) }' > fs/pstore/ramoops.mod
