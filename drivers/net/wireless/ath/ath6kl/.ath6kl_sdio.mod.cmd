cmd_drivers/net/wireless/ath/ath6kl/ath6kl_sdio.mod := printf '%s\n'   sdio.o | awk '!x[$$0]++ { print("drivers/net/wireless/ath/ath6kl/"$$0) }' > drivers/net/wireless/ath/ath6kl/ath6kl_sdio.mod
