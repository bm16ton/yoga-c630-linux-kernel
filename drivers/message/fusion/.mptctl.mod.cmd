cmd_drivers/message/fusion/mptctl.mod := printf '%s\n'   mptctl.o | awk '!x[$$0]++ { print("drivers/message/fusion/"$$0) }' > drivers/message/fusion/mptctl.mod
