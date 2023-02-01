cmd_drivers/misc/apds990x.mod := printf '%s\n'   apds990x.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/apds990x.mod
