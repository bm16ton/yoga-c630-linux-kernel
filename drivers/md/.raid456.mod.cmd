cmd_drivers/md/raid456.mod := printf '%s\n'   raid5.o raid5-cache.o raid5-ppl.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/raid456.mod
