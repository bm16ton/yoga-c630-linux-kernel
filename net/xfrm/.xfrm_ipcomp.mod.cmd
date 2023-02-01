cmd_net/xfrm/xfrm_ipcomp.mod := printf '%s\n'   xfrm_ipcomp.o | awk '!x[$$0]++ { print("net/xfrm/"$$0) }' > net/xfrm/xfrm_ipcomp.mod
