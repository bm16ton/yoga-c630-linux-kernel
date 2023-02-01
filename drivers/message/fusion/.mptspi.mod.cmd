cmd_drivers/message/fusion/mptspi.mod := printf '%s\n'   mptspi.o | awk '!x[$$0]++ { print("drivers/message/fusion/"$$0) }' > drivers/message/fusion/mptspi.mod
