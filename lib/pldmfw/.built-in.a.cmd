cmd_lib/pldmfw/built-in.a := rm -f lib/pldmfw/built-in.a;  printf "lib/pldmfw/%s " pldmfw.o | xargs ar cDPrST lib/pldmfw/built-in.a
