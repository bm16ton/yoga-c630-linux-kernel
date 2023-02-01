cmd_drivers/net/wireless/admtek/adm8211.mod := printf '%s\n'   adm8211.o | awk '!x[$$0]++ { print("drivers/net/wireless/admtek/"$$0) }' > drivers/net/wireless/admtek/adm8211.mod
