KERNELRELEASE := $(shell uname -r)
KDIR := /lib/modules/$(KERNELRELEASE)/build
obj-m += dependent.o

.PHONY: default
default:
	$(MAKE) -C "$(KDIR)" M="$$(pwd)"

.PHONY: install
install: default
	$(MAKE) -C "$(KDIR)" M="$$(pwd)" install

.PHONY: clean
clean:
	$(MAKE) O="$$(pwd)" -C "$(KDIR)" M="$$(pwd)" clean
