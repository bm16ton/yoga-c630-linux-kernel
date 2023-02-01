cmd_drivers/misc/hmc6352.mod := printf '%s\n'   hmc6352.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/hmc6352.mod
