cmd_sound/pci/snd-als300.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o sound/pci/snd-als300.ko sound/pci/snd-als300.o sound/pci/snd-als300.mod.o;  true
