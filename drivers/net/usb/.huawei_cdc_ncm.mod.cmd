cmd_drivers/net/usb/huawei_cdc_ncm.mod := printf '%s\n'   huawei_cdc_ncm.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/huawei_cdc_ncm.mod
