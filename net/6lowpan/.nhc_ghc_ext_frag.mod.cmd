cmd_net/6lowpan/nhc_ghc_ext_frag.mod := printf '%s\n'   nhc_ghc_ext_frag.o | awk '!x[$$0]++ { print("net/6lowpan/"$$0) }' > net/6lowpan/nhc_ghc_ext_frag.mod
