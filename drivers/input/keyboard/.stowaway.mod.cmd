cmd_drivers/input/keyboard/stowaway.mod := printf '%s\n'   stowaway.o | awk '!x[$$0]++ { print("drivers/input/keyboard/"$$0) }' > drivers/input/keyboard/stowaway.mod
