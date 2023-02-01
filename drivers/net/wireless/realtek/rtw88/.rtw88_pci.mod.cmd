cmd_drivers/net/wireless/realtek/rtw88/rtw88_pci.mod := printf '%s\n'   pci.o | awk '!x[$$0]++ { print("drivers/net/wireless/realtek/rtw88/"$$0) }' > drivers/net/wireless/realtek/rtw88/rtw88_pci.mod
