cmd_net/mpls/mpls_router.mod := printf '%s\n'   af_mpls.o | awk '!x[$$0]++ { print("net/mpls/"$$0) }' > net/mpls/mpls_router.mod
