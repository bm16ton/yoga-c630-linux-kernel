cmd_drivers/misc/enclosure.mod := printf '%s\n'   enclosure.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/enclosure.mod
