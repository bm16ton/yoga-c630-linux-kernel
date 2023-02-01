cmd_drivers/cdrom/cdrom.mod := printf '%s\n'   cdrom.o | awk '!x[$$0]++ { print("drivers/cdrom/"$$0) }' > drivers/cdrom/cdrom.mod
