cmd_drivers/mux/mux-adg792a.mod := printf '%s\n'   adg792a.o | awk '!x[$$0]++ { print("drivers/mux/"$$0) }' > drivers/mux/mux-adg792a.mod
