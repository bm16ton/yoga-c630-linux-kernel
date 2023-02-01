cmd_drivers/tee/tee.mod := printf '%s\n'   tee_core.o tee_shm.o tee_shm_pool.o | awk '!x[$$0]++ { print("drivers/tee/"$$0) }' > drivers/tee/tee.mod
