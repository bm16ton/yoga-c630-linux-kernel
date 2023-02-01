cmd_drivers/infiniband/ulp/isert/ib_isert.mod := printf '%s\n'   ib_isert.o | awk '!x[$$0]++ { print("drivers/infiniband/ulp/isert/"$$0) }' > drivers/infiniband/ulp/isert/ib_isert.mod
