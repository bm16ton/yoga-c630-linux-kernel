cmd_drivers/perf/thunderx2_pmu.mod := printf '%s\n'   thunderx2_pmu.o | awk '!x[$$0]++ { print("drivers/perf/"$$0) }' > drivers/perf/thunderx2_pmu.mod
