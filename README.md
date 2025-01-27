# Differentail Equations solver
Repository presents solution to task from AGH Course of Differentail Equations. The task was to implement FDM and FEM solutions to differential equation:
### Math part:


<img src="[sciezka/do/obrazu.png](https://github.com/mcjwsn/Differential-Equations-FDM-and-FEM-solutions-with-Python-Julia-Cpp/blob/main/Math.png]" style='alignement: center'>

### Coding part was impelemented with python (FEM) and julia,C++(FDM).
Visualization in python was created using matplotlib and numpy, in Julia using Plot library.

[Code in Python](https://przykladowa-strona.p][https://github.com/mcjwsn/Differential-Equations-FDM-and-FEM-solutions-with-Python-Julia-Cpp/blob/main/FEM-python.py)

To run:
```bash
python3 FEM-python.py
```
Code requires matplotlib and numpy

[Code in Julia](https://github.com/mcjwsn/Differential-Equations-FDM-and-FEM-solutions-with-Python-Julia-Cpp/blob/main/FDM_julia.jl)

To run:
```bash
julia FDM-julia.jl
```
Code requires Plot dictionary

[Code in C++](https://github.com/mcjwsn/Differential-Equations-FDM-and-FEM-solutions-with-Python-Julia-Cpp/blob/main/FDM_cpp.cpp)

To run:
```bash
g++ -o solver FDM_cpp.cpp
./solver
```
### Solutions for 100 points on Plot
#### Python
<img src="[sciezka/do/obrazu.png](https://github.com/mcjwsn/Differential-Equations-FDM-and-FEM-solutions-with-Python-Julia-Cpp/blob/main/FEM_python_chart.png)" width="400" height="400">

#### Julia
<img src="[sciezka/do/obrazu.png](https://github.com/mcjwsn/Differential-Equations-FDM-and-FEM-solutions-with-Python-Julia-Cpp/blob/main/FDM_julia_chart.png)" width="400" height="400">

#### C++
<img src="[sciezka/do/obrazu.png](https://github.com/mcjwsn/Differential-Equations-FDM-and-FEM-solutions-with-Python-Julia-Cpp/blob/main/FDM_cpp_chart.png)" width="400" height="400">
