cmd_net/6lowpan/nhc_ghc_ext_hop.mod := printf '%s\n'   nhc_ghc_ext_hop.o | awk '!x[$$0]++ { print("net/6lowpan/"$$0) }' > net/6lowpan/nhc_ghc_ext_hop.mod
