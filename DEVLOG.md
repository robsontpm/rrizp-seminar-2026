# Development Log

## FEATURE: Biffurcation diagram
- Implemented `biffurcation.h` and `biffurcation.cpp` encapsulating logic to generate the bifurcation diagram for the Roessler ODE.
- Computed the diagram using a parameter sweep over $c \in [c_{min}, c_{max}]$ using a Poincare map on the section $y=0$.
- Created the executable `nonrig-biff` (in `nonrig_biff_main.cpp`) which parses command-line parameters utilizing `getopt_long`.
- Added automated unit tests using Boost.Test in `test_biffurcation.cpp`.
- Successfully compiled code and tested its functionality locally.
