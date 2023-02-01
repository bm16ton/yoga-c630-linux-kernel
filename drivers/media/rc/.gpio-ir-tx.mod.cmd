cmd_drivers/media/rc/gpio-ir-tx.mod := printf '%s\n'   gpio-ir-tx.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/gpio-ir-tx.mod
