cmd_drivers/char/ipmi/ipmi_poweroff.mod := printf '%s\n'   ipmi_poweroff.o | awk '!x[$$0]++ { print("drivers/char/ipmi/"$$0) }' > drivers/char/ipmi/ipmi_poweroff.mod
