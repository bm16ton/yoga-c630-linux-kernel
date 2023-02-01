cmd_drivers/net/ppp/ppp_mppe.mod := printf '%s\n'   ppp_mppe.o | awk '!x[$$0]++ { print("drivers/net/ppp/"$$0) }' > drivers/net/ppp/ppp_mppe.mod
