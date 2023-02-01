cmd_sound/soc/qcom/snd-soc-sdm845.mod := printf '%s\n'   sdm845.o | awk '!x[$$0]++ { print("sound/soc/qcom/"$$0) }' > sound/soc/qcom/snd-soc-sdm845.mod
