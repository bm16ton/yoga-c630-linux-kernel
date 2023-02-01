cmd_drivers/target/loopback/tcm_loop.mod := printf '%s\n'   tcm_loop.o | awk '!x[$$0]++ { print("drivers/target/loopback/"$$0) }' > drivers/target/loopback/tcm_loop.mod
