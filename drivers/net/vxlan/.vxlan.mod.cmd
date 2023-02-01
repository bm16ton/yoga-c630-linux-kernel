cmd_drivers/net/vxlan/vxlan.mod := printf '%s\n'   vxlan_core.o vxlan_multicast.o vxlan_vnifilter.o | awk '!x[$$0]++ { print("drivers/net/vxlan/"$$0) }' > drivers/net/vxlan/vxlan.mod
