cmd_net/wireless/lib80211.mod := printf '%s\n'   lib80211.o | awk '!x[$$0]++ { print("net/wireless/"$$0) }' > net/wireless/lib80211.mod
