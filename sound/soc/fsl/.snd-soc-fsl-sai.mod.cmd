cmd_sound/soc/fsl/snd-soc-fsl-sai.mod := printf '%s\n'   fsl_sai.o | awk '!x[$$0]++ { print("sound/soc/fsl/"$$0) }' > sound/soc/fsl/snd-soc-fsl-sai.mod
