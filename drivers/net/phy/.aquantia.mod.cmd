cmd_drivers/net/phy/aquantia.mod := printf '%s\n'   aquantia_main.o aquantia_hwmon.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/aquantia.mod
