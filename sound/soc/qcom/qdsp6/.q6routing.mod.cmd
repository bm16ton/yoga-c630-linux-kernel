cmd_sound/soc/qcom/qdsp6/q6routing.mod := printf '%s\n'   q6routing.o | awk '!x[$$0]++ { print("sound/soc/qcom/qdsp6/"$$0) }' > sound/soc/qcom/qdsp6/q6routing.mod
