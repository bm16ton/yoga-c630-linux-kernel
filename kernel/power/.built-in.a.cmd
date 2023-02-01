cmd_kernel/power/built-in.a := rm -f kernel/power/built-in.a;  printf "kernel/power/%s " qos.o main.o console.o process.o suspend.o poweroff.o energy_model.o | xargs ar cDPrST kernel/power/built-in.a
