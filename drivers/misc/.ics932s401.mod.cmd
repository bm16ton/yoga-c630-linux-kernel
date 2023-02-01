cmd_drivers/misc/ics932s401.mod := printf '%s\n'   ics932s401.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/ics932s401.mod
