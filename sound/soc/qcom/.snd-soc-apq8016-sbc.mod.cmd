cmd_sound/soc/qcom/snd-soc-apq8016-sbc.mod := printf '%s\n'   apq8016_sbc.o | awk '!x[$$0]++ { print("sound/soc/qcom/"$$0) }' > sound/soc/qcom/snd-soc-apq8016-sbc.mod
