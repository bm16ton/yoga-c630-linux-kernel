cmd_drivers/net/team/team_mode_roundrobin.mod := printf '%s\n'   team_mode_roundrobin.o | awk '!x[$$0]++ { print("drivers/net/team/"$$0) }' > drivers/net/team/team_mode_roundrobin.mod
