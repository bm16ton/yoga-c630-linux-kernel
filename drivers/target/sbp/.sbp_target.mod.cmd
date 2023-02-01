cmd_drivers/target/sbp/sbp_target.mod := printf '%s\n'   sbp_target.o | awk '!x[$$0]++ { print("drivers/target/sbp/"$$0) }' > drivers/target/sbp/sbp_target.mod
