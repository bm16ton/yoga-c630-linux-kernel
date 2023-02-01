cmd_sound/pci/hda/snd-hda-codec-hdmi.mod := printf '%s\n'   patch_hdmi.o hda_eld.o | awk '!x[$$0]++ { print("sound/pci/hda/"$$0) }' > sound/pci/hda/snd-hda-codec-hdmi.mod
