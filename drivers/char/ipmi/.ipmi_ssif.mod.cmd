cmd_drivers/char/ipmi/ipmi_ssif.mod := printf '%s\n'   ipmi_ssif.o | awk '!x[$$0]++ { print("drivers/char/ipmi/"$$0) }' > drivers/char/ipmi/ipmi_ssif.mod
