cmd_drivers/net/can/softing/softing.mod := printf '%s\n'   softing_main.o softing_fw.o | awk '!x[$$0]++ { print("drivers/net/can/softing/"$$0) }' > drivers/net/can/softing/softing.mod
