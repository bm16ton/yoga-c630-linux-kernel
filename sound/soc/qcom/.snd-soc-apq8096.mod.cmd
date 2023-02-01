cmd_sound/soc/qcom/snd-soc-apq8096.mod := printf '%s\n'   apq8096.o | awk '!x[$$0]++ { print("sound/soc/qcom/"$$0) }' > sound/soc/qcom/snd-soc-apq8096.mod
