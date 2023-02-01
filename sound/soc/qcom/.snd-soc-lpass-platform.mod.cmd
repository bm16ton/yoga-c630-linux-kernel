cmd_sound/soc/qcom/snd-soc-lpass-platform.mod := printf '%s\n'   lpass-platform.o | awk '!x[$$0]++ { print("sound/soc/qcom/"$$0) }' > sound/soc/qcom/snd-soc-lpass-platform.mod
