cmd_drivers/media/pci/tw68/tw68.mod := printf '%s\n'   tw68-core.o tw68-video.o tw68-risc.o | awk '!x[$$0]++ { print("drivers/media/pci/tw68/"$$0) }' > drivers/media/pci/tw68/tw68.mod
