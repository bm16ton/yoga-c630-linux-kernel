cmd_drivers/char/ipmi/ipmi_devintf.mod := printf '%s\n'   ipmi_devintf.o | awk '!x[$$0]++ { print("drivers/char/ipmi/"$$0) }' > drivers/char/ipmi/ipmi_devintf.mod
