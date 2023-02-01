cmd_sound/soc/qcom/qdsp6/snd-q6apm.mod := printf '%s\n'   q6apm.o audioreach.o topology.o | awk '!x[$$0]++ { print("sound/soc/qcom/qdsp6/"$$0) }' > sound/soc/qcom/qdsp6/snd-q6apm.mod
