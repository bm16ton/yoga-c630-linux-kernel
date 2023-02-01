cmd_arch/arm64/crypto/chacha-neon.mod := printf '%s\n'   chacha-neon-core.o chacha-neon-glue.o | awk '!x[$$0]++ { print("arch/arm64/crypto/"$$0) }' > arch/arm64/crypto/chacha-neon.mod
