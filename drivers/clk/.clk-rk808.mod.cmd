cmd_drivers/clk/clk-rk808.mod := printf '%s\n'   clk-rk808.o | awk '!x[$$0]++ { print("drivers/clk/"$$0) }' > drivers/clk/clk-rk808.mod
