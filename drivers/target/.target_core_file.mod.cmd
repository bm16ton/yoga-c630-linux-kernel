cmd_drivers/target/target_core_file.mod := printf '%s\n'   target_core_file.o | awk '!x[$$0]++ { print("drivers/target/"$$0) }' > drivers/target/target_core_file.mod
