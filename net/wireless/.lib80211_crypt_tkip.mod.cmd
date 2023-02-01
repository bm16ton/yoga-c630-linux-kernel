cmd_net/wireless/lib80211_crypt_tkip.mod := printf '%s\n'   lib80211_crypt_tkip.o | awk '!x[$$0]++ { print("net/wireless/"$$0) }' > net/wireless/lib80211_crypt_tkip.mod
