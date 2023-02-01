cmd_sound/soc/qcom/qdsp6/q6apm-dai.mod := printf '%s\n'   q6apm-dai.o | awk '!x[$$0]++ { print("sound/soc/qcom/qdsp6/"$$0) }' > sound/soc/qcom/qdsp6/q6apm-dai.mod
