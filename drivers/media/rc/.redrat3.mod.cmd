cmd_drivers/media/rc/redrat3.mod := printf '%s\n'   redrat3.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/redrat3.mod
