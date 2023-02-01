cmd_drivers/target/tcm_fc/tcm_fc.mod := printf '%s\n'   tfc_cmd.o tfc_conf.o tfc_io.o tfc_sess.o | awk '!x[$$0]++ { print("drivers/target/tcm_fc/"$$0) }' > drivers/target/tcm_fc/tcm_fc.mod
