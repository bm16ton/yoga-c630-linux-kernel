cmd_drivers/nfc/nfcmrvl/nfcmrvl.mod := printf '%s\n'   main.o fw_dnld.o | awk '!x[$$0]++ { print("drivers/nfc/nfcmrvl/"$$0) }' > drivers/nfc/nfcmrvl/nfcmrvl.mod
