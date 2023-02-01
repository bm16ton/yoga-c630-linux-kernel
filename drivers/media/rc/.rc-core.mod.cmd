cmd_drivers/media/rc/rc-core.mod := printf '%s\n'   rc-main.o rc-ir-raw.o lirc_dev.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/rc-core.mod
