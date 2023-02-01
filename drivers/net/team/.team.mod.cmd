cmd_drivers/net/team/team.mod := printf '%s\n'   team.o | awk '!x[$$0]++ { print("drivers/net/team/"$$0) }' > drivers/net/team/team.mod
