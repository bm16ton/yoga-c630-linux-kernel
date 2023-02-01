cmd_arch/arm64/lib/xor-neon.mod := printf '%s\n'   xor-neon.o | awk '!x[$$0]++ { print("arch/arm64/lib/"$$0) }' > arch/arm64/lib/xor-neon.mod
