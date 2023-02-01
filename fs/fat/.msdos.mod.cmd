cmd_fs/fat/msdos.mod := printf '%s\n'   namei_msdos.o | awk '!x[$$0]++ { print("fs/fat/"$$0) }' > fs/fat/msdos.mod
