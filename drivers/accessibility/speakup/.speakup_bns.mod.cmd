cmd_drivers/accessibility/speakup/speakup_bns.mod := printf '%s\n'   speakup_bns.o | awk '!x[$$0]++ { print("drivers/accessibility/speakup/"$$0) }' > drivers/accessibility/speakup/speakup_bns.mod
