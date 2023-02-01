cmd_sound/soc/qcom/qdsp6/q6apm-lpass-dais.mod := printf '%s\n'   q6apm-lpass-dais.o | awk '!x[$$0]++ { print("sound/soc/qcom/qdsp6/"$$0) }' > sound/soc/qcom/qdsp6/q6apm-lpass-dais.mod
