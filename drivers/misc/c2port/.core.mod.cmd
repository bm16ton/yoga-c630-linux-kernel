cmd_drivers/misc/c2port/core.mod := printf '%s\n'   core.o | awk '!x[$$0]++ { print("drivers/misc/c2port/"$$0) }' > drivers/misc/c2port/core.mod
