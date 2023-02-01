cmd_drivers/mailbox/mailbox-xgene-slimpro.mod := printf '%s\n'   mailbox-xgene-slimpro.o | awk '!x[$$0]++ { print("drivers/mailbox/"$$0) }' > drivers/mailbox/mailbox-xgene-slimpro.mod
