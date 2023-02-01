cmd_drivers/usb/typec/mux/fsa4480.mod := printf '%s\n'   fsa4480.o | awk '!x[$$0]++ { print("drivers/usb/typec/mux/"$$0) }' > drivers/usb/typec/mux/fsa4480.mod
