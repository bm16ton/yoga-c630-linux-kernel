cmd_net/openvswitch/vport-vxlan.mod := printf '%s\n'   vport-vxlan.o | awk '!x[$$0]++ { print("net/openvswitch/"$$0) }' > net/openvswitch/vport-vxlan.mod
