cmd_net/openvswitch/vport-geneve.mod := printf '%s\n'   vport-geneve.o | awk '!x[$$0]++ { print("net/openvswitch/"$$0) }' > net/openvswitch/vport-geneve.mod
