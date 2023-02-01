cmd_arch/arm64/crypto/sha256-arm64.mod := printf '%s\n'   sha256-glue.o sha256-core.o | awk '!x[$$0]++ { print("arch/arm64/crypto/"$$0) }' > arch/arm64/crypto/sha256-arm64.mod
