cmd_sound/soc/qcom/qdsp6/q6adm.mod := printf '%s\n'   q6adm.o | awk '!x[$$0]++ { print("sound/soc/qcom/qdsp6/"$$0) }' > sound/soc/qcom/qdsp6/q6adm.mod
