cmd_drivers/misc/isl29003.mod := printf '%s\n'   isl29003.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/isl29003.mod
