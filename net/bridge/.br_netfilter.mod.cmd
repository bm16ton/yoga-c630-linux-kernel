cmd_net/bridge/br_netfilter.mod := printf '%s\n'   br_netfilter_hooks.o br_netfilter_ipv6.o | awk '!x[$$0]++ { print("net/bridge/"$$0) }' > net/bridge/br_netfilter.mod
