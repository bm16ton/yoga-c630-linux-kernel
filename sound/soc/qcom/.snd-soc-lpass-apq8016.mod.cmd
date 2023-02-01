cmd_sound/soc/qcom/snd-soc-lpass-apq8016.mod := printf '%s\n'   lpass-apq8016.o | awk '!x[$$0]++ { print("sound/soc/qcom/"$$0) }' > sound/soc/qcom/snd-soc-lpass-apq8016.mod
