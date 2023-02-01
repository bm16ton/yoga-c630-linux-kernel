cmd_drivers/media/rc/igorplugusb.mod := printf '%s\n'   igorplugusb.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/igorplugusb.mod
