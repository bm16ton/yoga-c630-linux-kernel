cmd_drivers/net/wwan/wwan.mod := printf '%s\n'   wwan_core.o | awk '!x[$$0]++ { print("drivers/net/wwan/"$$0) }' > drivers/net/wwan/wwan.mod
