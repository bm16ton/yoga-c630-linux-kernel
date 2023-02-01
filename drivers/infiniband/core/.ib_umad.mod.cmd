cmd_drivers/infiniband/core/ib_umad.mod := printf '%s\n'   user_mad.o | awk '!x[$$0]++ { print("drivers/infiniband/core/"$$0) }' > drivers/infiniband/core/ib_umad.mod
