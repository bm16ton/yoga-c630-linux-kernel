cmd_sound/soc/qcom/qdsp6/q6afe-dai.mod := printf '%s\n'   q6afe-dai.o | awk '!x[$$0]++ { print("sound/soc/qcom/qdsp6/"$$0) }' > sound/soc/qcom/qdsp6/q6afe-dai.mod
