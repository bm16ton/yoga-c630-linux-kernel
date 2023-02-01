cmd_drivers/message/fusion/mptsas.mod := printf '%s\n'   mptsas.o | awk '!x[$$0]++ { print("drivers/message/fusion/"$$0) }' > drivers/message/fusion/mptsas.mod
