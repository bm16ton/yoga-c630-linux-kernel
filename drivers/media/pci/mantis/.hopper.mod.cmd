cmd_drivers/media/pci/mantis/hopper.mod := printf '%s\n'   hopper_cards.o hopper_vp3028.o | awk '!x[$$0]++ { print("drivers/media/pci/mantis/"$$0) }' > drivers/media/pci/mantis/hopper.mod
