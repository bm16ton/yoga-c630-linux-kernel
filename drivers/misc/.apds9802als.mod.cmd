cmd_drivers/misc/apds9802als.mod := printf '%s\n'   apds9802als.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/apds9802als.mod
