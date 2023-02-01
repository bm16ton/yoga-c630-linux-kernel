cmd_drivers/target/target_core_iblock.mod := printf '%s\n'   target_core_iblock.o | awk '!x[$$0]++ { print("drivers/target/"$$0) }' > drivers/target/target_core_iblock.mod
