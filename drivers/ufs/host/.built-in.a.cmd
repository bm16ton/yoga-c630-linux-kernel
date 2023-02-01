cmd_drivers/ufs/host/built-in.a := rm -f drivers/ufs/host/built-in.a;  printf "drivers/ufs/host/%s " ufs-qcom.o ufs-qcom-ice.o ufshcd-pltfrm.o | xargs ar cDPrST drivers/ufs/host/built-in.a
