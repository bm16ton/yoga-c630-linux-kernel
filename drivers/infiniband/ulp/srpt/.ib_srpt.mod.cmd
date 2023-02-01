cmd_drivers/infiniband/ulp/srpt/ib_srpt.mod := printf '%s\n'   ib_srpt.o | awk '!x[$$0]++ { print("drivers/infiniband/ulp/srpt/"$$0) }' > drivers/infiniband/ulp/srpt/ib_srpt.mod
