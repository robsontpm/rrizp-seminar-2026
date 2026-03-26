# [DONE] RESEARCH: find periodic orbits for Roessler ODE

Create a program such that for given parametrs to the Roessler ODE, it finds periodic orbit by apllying fix point finding roblem P(x) = x for a Poincare map to some section.
- use CAPD capabilities
- define a suitable section and a Poincare map
- use iteration to search for apparently stable periodic orbits
- try to change the parameters from a regime where the orbit is apperently stable to a regime where it loses stability throug period doubling. Try to refine the orbit with Newton method. Try to find the period-2 orbit resulting from the biffurcation.
- check the stability of the orbits by computing eigenvalues of the Poincare map.