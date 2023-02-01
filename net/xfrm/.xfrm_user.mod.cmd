cmd_net/xfrm/xfrm_user.mod := printf '%s\n'   xfrm_user.o | awk '!x[$$0]++ { print("net/xfrm/"$$0) }' > net/xfrm/xfrm_user.mod
