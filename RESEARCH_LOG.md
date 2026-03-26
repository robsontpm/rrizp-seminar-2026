# Research Log

## ITERATION 1

- Formulated the `RESEARCH_GOAL.md` and `MATHEMATICS.md` to define the success criteria and mathematical basis.
- Planning to implement the basic skeleton for `find_periodic_orbits_main.cpp` using the CAPD library.
- The goal is to first implement a simple iterative search (repeatedly applying the Poincare map) to find an apparently stable orbit, and then implement Newton's method to refine it and calculate eigenvalues to check stability.

## ITERATION 2

- Implemented `find_periodic_orbits_main.cpp` containing iterative search, Newton's method, and eigenvalue stability checking.
- Successfully compiled the program.
- Ran the program with parameters $(a,b,c) = (0.2, 0.2, 2.5)$ and initial condition $(5,0,0)$.
- The iterative search converged to $(4.580816, 0, 1.526453)$ after 72 iterations.
- Newton's method successfully refined the point.
- Stability analysis showed eigenvalues of DP are approximately $-5.17 \times 10^{-6}$, $-0.77$, and $0$, successfully confirming that this period-1 orbit is STABLE.

## ITERATION 3

- Ran the program with parameters $(a,b,c) = (0.2, 0.2, 3.5)$ with `--period 1` to search for a period-1 orbit.
- The iterative search failed to converge after 100 iterations, indicating the period-1 orbit is unstable.
- Newton's method managed to find the unstable period-1 fixed point at $(6.128, 0, 1.859)$.
- Stability analysis yielded eigenvalues $\approx -8.69 \times 10^{-9}$, $-1.41$, and $0$. Since $|-1.41| > 1$, the period-1 orbit is confirmed to be UNSTABLE.
- Next, ran the program with parameters $(a,b,c) = (0.2, 0.2, 3.5)$ with `--period 2` to search for a period-2 orbit.
- The iterative search converged after 23 iterations.
- Newton's method refined the period-2 point to $(6.614, 0, 3.949)$.
- Stability analysis of the second iterate $DP^2$ yielded eigenvalues $\approx -3.88 \times 10^{-16}$, $-0.418$, and $-4.44 \times 10^{-16}$.
- Since the modulus of all eigenvalues is less than 1, the period-2 orbit is STABLE. This is consistent with a period-doubling bifurcation occurring between $c=2.5$ and $c=3.5$.
