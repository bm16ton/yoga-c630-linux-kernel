cmd_sound/soc/qcom/qdsp6/q6asm.mod := printf '%s\n'   q6asm.o | awk '!x[$$0]++ { print("sound/soc/qcom/qdsp6/"$$0) }' > sound/soc/qcom/qdsp6/q6asm.mod
