cmd_drivers/extcon/extcon-usbc-cros-ec.mod := printf '%s\n'   extcon-usbc-cros-ec.o | awk '!x[$$0]++ { print("drivers/extcon/"$$0) }' > drivers/extcon/extcon-usbc-cros-ec.mod
