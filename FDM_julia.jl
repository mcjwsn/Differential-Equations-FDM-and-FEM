using Plots
# bez liczenia calek
function solve_bvp(N) # n - liczba pktow przedizalow
    x = range(0, 2, length=N)# podzial na n podprzedzialow
    Δx = x[2] - x[1] # wyliczenia kroku
    
    # Tablica rozwiazan
    u = zeros(N)
    
    # Funckja sprezystosci
    E(x) = x <= 1 ? 2.0 : 10*(2.1-x)
    
    # lewa stron B(e,v)
    A = zeros(N, N)
    # prawa strona l(en)
    b = zeros(N)
    
    # warunek brzegowy drichleta
    u[end] = 20.0
    
    
    for i in 2:N-1
        # srodkowe punkty x_i-1, xi; xi, x_i+1
        x_mid_left = (x[i] + x[i-1]) / 2 
        x_mid_right = (x[i] + x[i+1]) / 2
        
        E_left = E(x_mid_left)
        E_right = E(x_mid_right)
        
        A[i, i-1] = E_left / Δx^2
        A[i, i] = -(E_left + E_right) / Δx^2
        A[i, i+1] = E_right / Δx^2
        
        b[i] = 1000 * sin(π * x[i]) # zmieniamy znaki z obu stron
    end
    
    # Brzegowy warunke na x = 0: du/dx + 2u = 10
    # szacowanie du/dx dla x=0
    A[1, 1] = -1/Δx + 2 # wsp przy u0
    A[1, 2] = 1/Δx # wsp przy u1
    b[1] = 10
    
    # A*u=b macierzowo
    u[1:N-1] = A[1:N-1, 1:N-1] \ b[1:N-1]
    
    return x, u
end

# Liczba punktow
N = 100
x, u = solve_bvp(N)

# Tworzenie folderu
if !isdir("Desktop/rurki")
    mkdir("Desktop/rurki")
end


# Wykres
plot(x, u, label="u(x)", xlabel="x", ylabel="u(x)", title="Solution to the BVP", linewidth=2, legend=:topright)

# Zapis
# dodac sciezke do pliku
savefig(joinpath("Desktop", "bvp_solution_julia.png"))