cmd_drivers/hwspinlock/built-in.a := rm -f drivers/hwspinlock/built-in.a;  printf "drivers/hwspinlock/%s " hwspinlock_core.o qcom_hwspinlock.o | xargs ar cDPrST drivers/hwspinlock/built-in.a
