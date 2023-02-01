cmd_sound/soc/qcom/snd-soc-qcom-common.mod := printf '%s\n'   common.o | awk '!x[$$0]++ { print("sound/soc/qcom/"$$0) }' > sound/soc/qcom/snd-soc-qcom-common.mod
