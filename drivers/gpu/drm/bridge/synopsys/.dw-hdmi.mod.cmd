cmd_drivers/gpu/drm/bridge/synopsys/dw-hdmi.mod := printf '%s\n'   dw-hdmi.o | awk '!x[$$0]++ { print("drivers/gpu/drm/bridge/synopsys/"$$0) }' > drivers/gpu/drm/bridge/synopsys/dw-hdmi.mod
