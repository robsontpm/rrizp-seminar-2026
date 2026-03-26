# Research Goal: Periodic Orbits in Roessler System

## Mathematically Plausible

The search for a periodic orbit is mathematically plausible if:
- It relies on searching for fixed points $P(x) - x = 0$ of the Poincare map $P$ for a well-defined transversal section.
- For period-2 orbits, it searches for fixed points of $P^2(x) - x = 0$.
- The Poincare map can be accurately integrated, and we can compute its Jacobian $DP$ using the variational equations.
- Stability is correctly assessed by calculating the eigenvalues of the Jacobian $DP(x)$ at the fixed point, where an orbit is stable if all eigenvalues have modulus strictly less than 1 (except the trivial eigenvalue 1 corresponding to the flow direction which is 0 for the Poincare map DP on the section).
- Newton's method correctly uses the Jacobian to refine the fixed point $x_{n+1} = x_n - (DP(x_n) - I)^{-1} (P(x_n) - x_n)$.

## Criteria for Success

- A program `find_periodic_orbits` is implemented utilizing CAPD to accurately identify both period-1 and period-2 orbits.
- The program demonstrates convergence using Newton's method.
- The program correctly reports the stability of the found orbit by calculating and checking the modulus of the eigenvalues of the Jacobian $DP$.
- The period-1 orbit is found and verified to be stable at a standard set of parameters.
- The parameters are varied to observe the loss of stability of the period-1 orbit and the emergence of a stable period-2 orbit (period doubling bifurcation).
