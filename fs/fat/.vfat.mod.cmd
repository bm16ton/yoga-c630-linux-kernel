cmd_fs/fat/vfat.mod := printf '%s\n'   namei_vfat.o | awk '!x[$$0]++ { print("fs/fat/"$$0) }' > fs/fat/vfat.mod
