cmd_ipc/built-in.a := rm -f ipc/built-in.a;  printf "ipc/%s " compat.o util.o msgutil.o msg.o sem.o shm.o syscall.o ipc_sysctl.o mqueue.o namespace.o mq_sysctl.o | xargs ar cDPrST ipc/built-in.a
