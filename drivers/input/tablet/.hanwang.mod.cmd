cmd_drivers/input/tablet/hanwang.mod := printf '%s\n'   hanwang.o | awk '!x[$$0]++ { print("drivers/input/tablet/"$$0) }' > drivers/input/tablet/hanwang.mod
