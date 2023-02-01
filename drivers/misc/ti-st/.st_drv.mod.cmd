cmd_drivers/misc/ti-st/st_drv.mod := printf '%s\n'   st_core.o st_kim.o st_ll.o | awk '!x[$$0]++ { print("drivers/misc/ti-st/"$$0) }' > drivers/misc/ti-st/st_drv.mod
