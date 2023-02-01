cmd_drivers/net/wireless/ath/ath6kl/ath6kl_usb.mod := printf '%s\n'   usb.o | awk '!x[$$0]++ { print("drivers/net/wireless/ath/ath6kl/"$$0) }' > drivers/net/wireless/ath/ath6kl/ath6kl_usb.mod
