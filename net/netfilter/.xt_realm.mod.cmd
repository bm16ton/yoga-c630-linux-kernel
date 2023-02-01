cmd_net/netfilter/xt_realm.mod := printf '%s\n'   xt_realm.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_realm.mod
