cmd_drivers/cpufreq/cpufreq_powersave.mod := printf '%s\n'   cpufreq_powersave.o | awk '!x[$$0]++ { print("drivers/cpufreq/"$$0) }' > drivers/cpufreq/cpufreq_powersave.mod
