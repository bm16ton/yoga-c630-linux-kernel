cmd_drivers/clk/clk-hi655x.mod := printf '%s\n'   clk-hi655x.o | awk '!x[$$0]++ { print("drivers/clk/"$$0) }' > drivers/clk/clk-hi655x.mod
