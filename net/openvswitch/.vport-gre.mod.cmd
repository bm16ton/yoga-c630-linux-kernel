cmd_net/openvswitch/vport-gre.mod := printf '%s\n'   vport-gre.o | awk '!x[$$0]++ { print("net/openvswitch/"$$0) }' > net/openvswitch/vport-gre.mod
