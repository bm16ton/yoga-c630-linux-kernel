cmd_drivers/net/wireless/ath/ar5523/ar5523.mod := printf '%s\n'   ar5523.o | awk '!x[$$0]++ { print("drivers/net/wireless/ath/ar5523/"$$0) }' > drivers/net/wireless/ath/ar5523/ar5523.mod
