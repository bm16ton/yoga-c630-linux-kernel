cmd_drivers/net/wireless/ath/ath11k/ath11k_pci.mod := printf '%s\n'   mhi.o pci.o | awk '!x[$$0]++ { print("drivers/net/wireless/ath/ath11k/"$$0) }' > drivers/net/wireless/ath/ath11k/ath11k_pci.mod
