cmd_drivers/net/wireless/ath/ath10k/ath10k_sdio.mod := printf '%s\n'   sdio.o | awk '!x[$$0]++ { print("drivers/net/wireless/ath/ath10k/"$$0) }' > drivers/net/wireless/ath/ath10k/ath10k_sdio.mod
