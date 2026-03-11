import numpy as np

A = np.loadtxt("A.txt", skiprows=1)
B = np.loadtxt("B.txt", skiprows=1)

C = A @ B

print("Python result:")
print(C)