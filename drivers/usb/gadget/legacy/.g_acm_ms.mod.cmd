cmd_drivers/usb/gadget/legacy/g_acm_ms.mod := printf '%s\n'   acm_ms.o | awk '!x[$$0]++ { print("drivers/usb/gadget/legacy/"$$0) }' > drivers/usb/gadget/legacy/g_acm_ms.mod
