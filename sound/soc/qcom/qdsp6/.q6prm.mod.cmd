cmd_sound/soc/qcom/qdsp6/q6prm.mod := printf '%s\n'   q6prm.o | awk '!x[$$0]++ { print("sound/soc/qcom/qdsp6/"$$0) }' > sound/soc/qcom/qdsp6/q6prm.mod
