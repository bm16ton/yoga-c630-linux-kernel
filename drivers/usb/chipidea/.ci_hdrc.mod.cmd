cmd_drivers/usb/chipidea/ci_hdrc.mod := printf '%s\n'   core.o otg.o debug.o ulpi.o udc.o trace.o host.o | awk '!x[$$0]++ { print("drivers/usb/chipidea/"$$0) }' > drivers/usb/chipidea/ci_hdrc.mod
