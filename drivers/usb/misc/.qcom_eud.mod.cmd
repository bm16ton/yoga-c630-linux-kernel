cmd_drivers/usb/misc/qcom_eud.mod := printf '%s\n'   qcom_eud.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/qcom_eud.mod
