cmd_drivers/net/team/team.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/team/team.ko drivers/net/team/team.o drivers/net/team/team.mod.o;  true
