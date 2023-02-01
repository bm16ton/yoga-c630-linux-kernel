cmd_drivers/usb/typec/tipd/tps6598x.mod := printf '%s\n'   core.o trace.o | awk '!x[$$0]++ { print("drivers/usb/typec/tipd/"$$0) }' > drivers/usb/typec/tipd/tps6598x.mod
