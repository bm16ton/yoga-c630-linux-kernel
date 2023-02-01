cmd_net/atm/mpoa.mod := printf '%s\n'   mpc.o mpoa_caches.o mpoa_proc.o | awk '!x[$$0]++ { print("net/atm/"$$0) }' > net/atm/mpoa.mod
