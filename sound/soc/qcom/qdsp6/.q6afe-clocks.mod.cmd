cmd_sound/soc/qcom/qdsp6/q6afe-clocks.mod := printf '%s\n'   q6afe-clocks.o | awk '!x[$$0]++ { print("sound/soc/qcom/qdsp6/"$$0) }' > sound/soc/qcom/qdsp6/q6afe-clocks.mod
