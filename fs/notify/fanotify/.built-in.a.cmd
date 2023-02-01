cmd_fs/notify/fanotify/built-in.a := rm -f fs/notify/fanotify/built-in.a;  printf "fs/notify/fanotify/%s " fanotify.o fanotify_user.o | xargs ar cDPrST fs/notify/fanotify/built-in.a
