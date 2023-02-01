cmd_sound/soc/fsl/snd-soc-fsl-utils.mod := printf '%s\n'   fsl_utils.o | awk '!x[$$0]++ { print("sound/soc/fsl/"$$0) }' > sound/soc/fsl/snd-soc-fsl-utils.mod
