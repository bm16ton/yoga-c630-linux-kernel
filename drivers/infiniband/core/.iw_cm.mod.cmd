cmd_drivers/infiniband/core/iw_cm.mod := printf '%s\n'   iwcm.o iwpm_util.o iwpm_msg.o | awk '!x[$$0]++ { print("drivers/infiniband/core/"$$0) }' > drivers/infiniband/core/iw_cm.mod
