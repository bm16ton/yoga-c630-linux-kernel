cmd_drivers/watchdog/meson_gxbb_wdt.mod := printf '%s\n'   meson_gxbb_wdt.o | awk '!x[$$0]++ { print("drivers/watchdog/"$$0) }' > drivers/watchdog/meson_gxbb_wdt.mod
