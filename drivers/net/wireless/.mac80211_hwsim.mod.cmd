cmd_drivers/net/wireless/mac80211_hwsim.mod := printf '%s\n'   mac80211_hwsim.o | awk '!x[$$0]++ { print("drivers/net/wireless/"$$0) }' > drivers/net/wireless/mac80211_hwsim.mod
