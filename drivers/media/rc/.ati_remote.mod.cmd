cmd_drivers/media/rc/ati_remote.mod := printf '%s\n'   ati_remote.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ati_remote.mod
