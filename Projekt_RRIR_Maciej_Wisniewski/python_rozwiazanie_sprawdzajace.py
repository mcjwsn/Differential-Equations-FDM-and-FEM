import numpy as np
from scipy.integrate import solve_bvp
import matplotlib.pyplot as plt

def E(x):
    return np.piecewise(x, [x <= 1, x > 1], [-2, -6])

def ode_system(x, y):
    E_vals = E(x)
    dydx = np.zeros_like(y)
    dydx[0] = y[1]  # y[0] = u, y[1] = du/dx
    dydx[1] = (-1000 * np.sin(np.pi * x)) / E_vals
    return dydx

def bc(ya, yb):
    return np.array([ya[1] + 2 * ya[0] - 10, yb[0] - 3])

n = 100
x = np.linspace(0, 2, n)
y_guess = np.zeros((2, x.size))

solution = solve_bvp(ode_system, bc, x, y_guess)

if solution.success:
    plt.plot(solution.x, solution.y[0], label="u(x)")
    plt.xlabel("x")
    plt.ylabel("u(x)")
    plt.title("Rozwiązanie równania odkształcenia sprężystego")
    plt.legend()
    plt.grid()
    plt.show()
else:
    print("Nie udało się znaleźć rozwiązania.")