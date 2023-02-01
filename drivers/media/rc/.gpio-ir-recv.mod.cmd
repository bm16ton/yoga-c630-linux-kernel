cmd_drivers/media/rc/gpio-ir-recv.mod := printf '%s\n'   gpio-ir-recv.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/gpio-ir-recv.mod
