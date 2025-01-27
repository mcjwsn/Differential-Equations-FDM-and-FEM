# RRIR Project
Repository presents solution task from AGH Course of Differentail Equations. The task was to implement FDM and FEM solutions to differential equation:
### Równanie wariacyjne:
\[
\int_{0}^{2} E(x) \frac{du(x)}{dx} \frac{dv(x)}{dx} \, dx - E(0) (10 - 2u(0)) v(0) = -1000 \int_{0}^{2} \sin(\pi x) v(x) \, dx
\]

### Warunki brzegowe:
\[
u(2) = 20
\]
\[
\frac{du(0)}{dx} + 2u(0) = 10
\]

### Definicja funkcji \(E(x)\):
\[
E(x) = 
\begin{cases} 
2 & \text{dla } x \in [0, 1] \\
21 - 10x & \text{dla } x \in (1, 2]
\end{cases}
\]
