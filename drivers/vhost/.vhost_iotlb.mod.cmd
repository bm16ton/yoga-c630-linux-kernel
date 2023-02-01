cmd_drivers/vhost/vhost_iotlb.mod := printf '%s\n'   iotlb.o | awk '!x[$$0]++ { print("drivers/vhost/"$$0) }' > drivers/vhost/vhost_iotlb.mod
