cmd_drivers/gpio/gpio-xgene-sb.mod := printf '%s\n'   gpio-xgene-sb.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-xgene-sb.mod
