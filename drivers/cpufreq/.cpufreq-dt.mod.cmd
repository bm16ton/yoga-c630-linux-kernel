cmd_drivers/cpufreq/cpufreq-dt.mod := printf '%s\n'   cpufreq-dt.o | awk '!x[$$0]++ { print("drivers/cpufreq/"$$0) }' > drivers/cpufreq/cpufreq-dt.mod
