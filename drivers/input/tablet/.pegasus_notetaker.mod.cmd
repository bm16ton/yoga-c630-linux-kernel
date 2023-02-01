cmd_drivers/input/tablet/pegasus_notetaker.mod := printf '%s\n'   pegasus_notetaker.o | awk '!x[$$0]++ { print("drivers/input/tablet/"$$0) }' > drivers/input/tablet/pegasus_notetaker.mod
