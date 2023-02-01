cmd_sound/soc/qcom/snd-soc-lpass-cpu.mod := printf '%s\n'   lpass-cpu.o | awk '!x[$$0]++ { print("sound/soc/qcom/"$$0) }' > sound/soc/qcom/snd-soc-lpass-cpu.mod
