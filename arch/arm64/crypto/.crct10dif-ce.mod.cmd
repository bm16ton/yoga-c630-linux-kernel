cmd_arch/arm64/crypto/crct10dif-ce.mod := printf '%s\n'   crct10dif-ce-core.o crct10dif-ce-glue.o | awk '!x[$$0]++ { print("arch/arm64/crypto/"$$0) }' > arch/arm64/crypto/crct10dif-ce.mod
