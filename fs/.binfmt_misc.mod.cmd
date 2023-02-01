cmd_fs/binfmt_misc.mod := printf '%s\n'   binfmt_misc.o | awk '!x[$$0]++ { print("fs/"$$0) }' > fs/binfmt_misc.mod
