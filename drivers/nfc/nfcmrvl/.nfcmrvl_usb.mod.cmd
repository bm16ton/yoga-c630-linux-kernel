cmd_drivers/nfc/nfcmrvl/nfcmrvl_usb.mod := printf '%s\n'   usb.o | awk '!x[$$0]++ { print("drivers/nfc/nfcmrvl/"$$0) }' > drivers/nfc/nfcmrvl/nfcmrvl_usb.mod
