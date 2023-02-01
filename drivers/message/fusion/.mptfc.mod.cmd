cmd_drivers/message/fusion/mptfc.mod := printf '%s\n'   mptfc.o | awk '!x[$$0]++ { print("drivers/message/fusion/"$$0) }' > drivers/message/fusion/mptfc.mod
