#!/bin/bash

# Experiment 1: Stable period-1 orbit
echo "--- Experiment 1: Stable period-1 orbit ---"
./build/find_periodic_orbits -a 0.2 -b 0.2 -c 2.5 --x0 5.0 --y0 0.0 --z0 0.0 --iter 100 --period 1 -o exp1_stable_p1

# Experiment 2: Unstable period-1 orbit (period doubling regime)
echo -e "\n--- Experiment 2: Unstable period-1 orbit ---"
./build/find_periodic_orbits -a 0.2 -b 0.2 -c 3.5 --x0 5.0 --y0 0.0 --z0 0.0 --iter 100 --period 1 -o exp2_unstable_p1

# Experiment 3: Stable period-2 orbit (period doubling regime)
echo -e "\n--- Experiment 3: Stable period-2 orbit ---"
./build/find_periodic_orbits -a 0.2 -b 0.2 -c 3.5 --x0 5.0 --y0 0.0 --z0 0.0 --iter 100 --period 2 -o exp3_stable_p2
