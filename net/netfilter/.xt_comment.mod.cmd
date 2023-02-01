cmd_net/netfilter/xt_comment.mod := printf '%s\n'   xt_comment.o | awk '!x[$$0]++ { print("net/netfilter/"$$0) }' > net/netfilter/xt_comment.mod
