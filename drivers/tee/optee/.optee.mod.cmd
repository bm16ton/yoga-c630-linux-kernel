cmd_drivers/tee/optee/optee.mod := printf '%s\n'   core.o call.o notif.o rpc.o supp.o device.o smc_abi.o ffa_abi.o | awk '!x[$$0]++ { print("drivers/tee/optee/"$$0) }' > drivers/tee/optee/optee.mod
