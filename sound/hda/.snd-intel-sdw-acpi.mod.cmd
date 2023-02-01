cmd_sound/hda/snd-intel-sdw-acpi.mod := printf '%s\n'   intel-sdw-acpi.o | awk '!x[$$0]++ { print("sound/hda/"$$0) }' > sound/hda/snd-intel-sdw-acpi.mod
