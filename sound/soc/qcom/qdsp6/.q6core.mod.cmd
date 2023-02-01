cmd_sound/soc/qcom/qdsp6/q6core.mod := printf '%s\n'   q6core.o | awk '!x[$$0]++ { print("sound/soc/qcom/qdsp6/"$$0) }' > sound/soc/qcom/qdsp6/q6core.mod
