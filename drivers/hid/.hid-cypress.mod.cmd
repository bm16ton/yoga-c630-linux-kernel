cmd_drivers/hid/hid-cypress.mod := printf '%s\n'   hid-cypress.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-cypress.mod
