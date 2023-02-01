cmd_drivers/clk/qcom/dispcc-sm8250.mod := printf '%s\n'   dispcc-sm8250.o | awk '!x[$$0]++ { print("drivers/clk/qcom/"$$0) }' > drivers/clk/qcom/dispcc-sm8250.mod
