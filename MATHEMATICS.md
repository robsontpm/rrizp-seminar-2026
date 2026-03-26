# Mathematics of Finding Periodic Orbits in the Roessler System

## Roessler ODE

The Roessler system is defined by the following system of ordinary differential equations (ODEs):
```
dx/dt = -y - z
dy/dt = x + a*y
dz/dt = b + z*(x - c)
```
where $a, b, c$ are parameters.

## Poincare Map

A Poincare map $P$ converts the continuous-time problem of finding periodic orbits into a discrete-time problem of finding fixed points.
We define a transversal section $\Sigma$, for instance, the plane $y=0$ crossed in a specific direction (e.g., $dy/dt > 0$, or `MinusPlus` crossing).
The Poincare map $P(x)$ takes a point $x \in \Sigma$ and returns the point where the trajectory starting at $x$ next intersects $\Sigma$ in the specified direction.
A periodic orbit of the ODE corresponds to a fixed point $x^*$ such that $P(x^*) = x^*$.
A period-$k$ orbit corresponds to a point $x^*$ such that $P^k(x^*) = x^*$ but $P^m(x^*) \neq x^*$ for $m < k$.

## Newton's Method for Fixed Points

To find the fixed point $x^*$ of $P(x)$, we want to find the root of the function $F(x) = P(x) - x = 0$.
Using Newton's method, we can iteratively refine an initial guess $x_0$:
$$x_{n+1} = x_n - [DF(x_n)]^{-1} F(x_n)$$
where $DF(x) = DP(x) - I$, and $I$ is the identity matrix.
$DP(x)$ is the Jacobian matrix of the Poincare map, which can be computed from the monodromy matrix (the fundamental matrix solution of the variational equations) evaluated at the return time.

## Stability Analysis

The stability of a periodic orbit corresponding to the fixed point $x^*$ is determined by the eigenvalues of the Jacobian matrix $DP(x^*)$.
- If all eigenvalues $\lambda_i$ of $DP(x^*)$ satisfy $|\lambda_i| < 1$, the periodic orbit is asymptotically stable.
- If at least one eigenvalue satisfies $|\lambda_i| > 1$, the periodic orbit is unstable.
Note that for an ODE system, the monodromy matrix has a trivial eigenvalue $\lambda=1$ corresponding to perturbations along the direction of the flow. However, when restricted to the Poincare section, this trivial eigenvalue maps to $0$ in $DP(x)$. For a 3D system like Roessler and a 2D section, $DP(x)$ will effectively have two non-zero eigenvalues that determine stability.
