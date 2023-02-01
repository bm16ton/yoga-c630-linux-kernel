cmd_drivers/accessibility/speakup/speakup_ltlk.mod := printf '%s\n'   speakup_ltlk.o | awk '!x[$$0]++ { print("drivers/accessibility/speakup/"$$0) }' > drivers/accessibility/speakup/speakup_ltlk.mod
