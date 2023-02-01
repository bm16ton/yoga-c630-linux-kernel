cmd_drivers/md/dm-snapshot.mod := printf '%s\n'   dm-snap.o dm-exception-store.o dm-snap-transient.o dm-snap-persistent.o | awk '!x[$$0]++ { print("drivers/md/"$$0) }' > drivers/md/dm-snapshot.mod
