cmd_drivers/net/wireless/ath/ath10k/ath10k_usb.mod := printf '%s\n'   usb.o | awk '!x[$$0]++ { print("drivers/net/wireless/ath/ath10k/"$$0) }' > drivers/net/wireless/ath/ath10k/ath10k_usb.mod
