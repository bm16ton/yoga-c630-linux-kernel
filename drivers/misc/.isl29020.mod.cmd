cmd_drivers/misc/isl29020.mod := printf '%s\n'   isl29020.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/isl29020.mod
