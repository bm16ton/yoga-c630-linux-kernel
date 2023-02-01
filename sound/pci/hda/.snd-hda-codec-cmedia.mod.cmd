cmd_sound/pci/hda/snd-hda-codec-cmedia.mod := printf '%s\n'   patch_cmedia.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-codec-cmedia.mod
