cmd_drivers/infiniband/ulp/srp/ib_srp.mod := printf '%s\n'   ib_srp.o | awk '!x[$$0]++ { print("drivers/infiniband/ulp/srp/"$$0) }' > drivers/infiniband/ulp/srp/ib_srp.mod
