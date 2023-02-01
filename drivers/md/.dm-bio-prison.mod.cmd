cmd_drivers/md/dm-bio-prison.mod := printf '%s\n'   dm-bio-prison-v1.o dm-bio-prison-v2.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-bio-prison.mod
