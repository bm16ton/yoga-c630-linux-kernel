cmd_kernel/configs.mod := printf '%s\n'   configs.o | awk '!x[$$0]++ { print("kernel/"$$0) }' > kernel/configs.mod
