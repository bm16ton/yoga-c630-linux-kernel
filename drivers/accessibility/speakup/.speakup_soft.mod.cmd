cmd_drivers/accessibility/speakup/speakup_soft.mod := printf '%s\n'   speakup_soft.o | awk '!x[$$0]++ { print("drivers/accessibility/speakup/"$$0) }' > drivers/accessibility/speakup/speakup_soft.mod
