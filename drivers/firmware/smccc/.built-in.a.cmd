cmd_drivers/firmware/smccc/built-in.a := rm -f drivers/firmware/smccc/built-in.a;  printf "drivers/firmware/smccc/%s " smccc.o kvm_guest.o soc_id.o | xargs ar cDPrST drivers/firmware/smccc/built-in.a
