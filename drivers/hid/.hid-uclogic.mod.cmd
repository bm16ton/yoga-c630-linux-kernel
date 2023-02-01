cmd_drivers/hid/hid-uclogic.mod := printf '%s\n'   hid-uclogic-core.o hid-uclogic-rdesc.o hid-uclogic-params.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-uclogic.mod
