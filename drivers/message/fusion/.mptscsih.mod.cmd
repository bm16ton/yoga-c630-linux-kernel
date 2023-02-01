cmd_drivers/message/fusion/mptscsih.mod := printf '%s\n'   mptscsih.o | awk '!x[$$0]++ { print("drivers/message/fusion/"$$0) }' > drivers/message/fusion/mptscsih.mod
