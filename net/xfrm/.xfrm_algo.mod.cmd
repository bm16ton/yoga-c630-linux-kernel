cmd_net/xfrm/xfrm_algo.mod := printf '%s\n'   xfrm_algo.o | awk '!x[$$0]++ { print("net/xfrm/"$$0) }' > net/xfrm/xfrm_algo.mod
