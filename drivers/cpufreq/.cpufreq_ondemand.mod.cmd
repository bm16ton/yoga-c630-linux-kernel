cmd_drivers/cpufreq/cpufreq_ondemand.mod := printf '%s\n'   cpufreq_ondemand.o | awk '!x[$$0]++ { print("drivers/cpufreq/"$$0) }' > drivers/cpufreq/cpufreq_ondemand.mod
