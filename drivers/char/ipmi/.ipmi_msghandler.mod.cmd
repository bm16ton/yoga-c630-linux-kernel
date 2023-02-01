cmd_drivers/char/ipmi/ipmi_msghandler.mod := printf '%s\n'   ipmi_msghandler.o | awk '!x[$$0]++ { print("drivers/char/ipmi/"$$0) }' > drivers/char/ipmi/ipmi_msghandler.mod
