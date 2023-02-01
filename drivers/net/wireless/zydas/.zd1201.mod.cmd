cmd_drivers/net/wireless/zydas/zd1201.mod := printf '%s\n'   zd1201.o | awk '!x[$$0]++ { print("drivers/net/wireless/zydas/"$$0) }' > drivers/net/wireless/zydas/zd1201.mod
