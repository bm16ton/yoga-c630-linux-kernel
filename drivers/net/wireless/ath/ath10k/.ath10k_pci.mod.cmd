cmd_drivers/net/wireless/ath/ath10k/ath10k_pci.mod := printf '%s\n'   pci.o | awk '!x[$$0]++ { print("drivers/net/wireless/ath/ath10k/"$$0) }' > drivers/net/wireless/ath/ath10k/ath10k_pci.mod
