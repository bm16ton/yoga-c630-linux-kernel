cmd_drivers/clk/qcom/camcc-sdm845.mod := printf '%s\n'   camcc-sdm845.o | awk '!x[$$0]++ { print("drivers/clk/qcom/"$$0) }' > drivers/clk/qcom/camcc-sdm845.mod
