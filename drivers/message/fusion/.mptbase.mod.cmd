cmd_drivers/message/fusion/mptbase.mod := printf '%s\n'   mptbase.o | awk '!x[$$0]++ { print("drivers/message/fusion/"$$0) }' > drivers/message/fusion/mptbase.mod
