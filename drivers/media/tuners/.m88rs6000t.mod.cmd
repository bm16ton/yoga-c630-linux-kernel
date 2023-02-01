cmd_drivers/media/tuners/m88rs6000t.mod := printf '%s\n'   m88rs6000t.o | awk '!x[$$0]++ { print("drivers/media/tuners/"$$0) }' > drivers/media/tuners/m88rs6000t.mod
