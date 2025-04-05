# rozwiazanie rownania po modyfikacji
import numpy as np
from scipy import integrate
import matplotlib.pyplot as plt
# rozwiazanie z calkami
# liczenia v,w tak jak w skrypcie
def e(i, x, h):
    """
    Definiuje funkcję bazową e_i(x).
    """
    if x < h * (i - 1) or x > h * (i + 1):
        return 0
    if x < h * i:
        return x / h - i + 1
    return -x / h + i + 1

def e_prim(i, x, h):
    """
    Definiuje pochodną funkcji bazowej e_i(x).
    """
    if x < h * (i - 1) or x > h * (i + 1):
        return 0
    if x < h * i:
        return 1 / h
    return -1 / h
#r macierz B(v,w)
def B(i, j, s, k, h):
    """
    Oblicza element B(v, w) macierzy sztywności.
    """
    def E(x):
        return 2 if 0 <= x <= 1 else 10*(2.1-x)
    return integrate.quad((lambda x: E(x) * e_prim(i, x, h) * e_prim(j, x, h)), s, k)[0] - 4 * e(i, 0, h) * e(j, 0, h)
# macierz L(v)
def L(i, s, k, h):
    """
    Oblicza element L(v) wektora obciążenia.
    """
    return integrate.quad((lambda x: -1000 * np.sin(np.pi * x) * e(i, x, h)), s, k)[0] + 60 * e(i, 0, h)

def create_A(n, h):
    """
    Tworzy macierz A o rozmiarze n x n.
    """
    def find_row(i,n):
        row = []
        for j in range(n):
            if abs(j-i) > 1:
                row.append(0) #spora część macierzy bedzie zerami co przyspieszy obliczenia
                continue
            if abs(i - j) == 1:
                s = 2 * max(0, min(i, j) / n)
                e = 2 * min(1, max(i, j) / n)
            else:
                s = 2 * max(0, (i - 1) / n)
                e = 2 * min(1, (i + 1) / n)
            row.append(B(i, j, s, e, h))
        return row
    return  [find_row(i,n) for i in range(n)] # macierz

def create_B(n, h):
    """
    Wektor l(v)
    """
    def find_sec_row(i,n):   
        s = 2.0 * max(0, (i - 1) / n)
        e = 2.0 * min(1, (i + 1) / n)
        return(L(i, s, e, h))
    return [find_sec_row(i,n) for i in range(n)] # macierz

def solve(n):
    """
    Rozwiązuje układ równań dla danego n.
    """
    h = 2 / n  # Długość przedziału
    a = np.array(create_A(n, h)) # lewa strona
    b = np.array(create_B(n, h)) # prawa strona

    # (x,y)
    return ([h * i for i in range(n + 1)], np.append(np.linalg.solve(a, b) + 20, 20))

def show(x, y, n):
    """
     wykres rozwiązania.
    """
    ax = plt.subplot()
    ax.set(title='Rozwiązanie dla n = ' + str(n), xlabel='x')
    ax.plot(x, y, color='red')
    plt.show()

# Działanie
x, y = solve(100)
show(x, y, 100)
