import numpy as np
import time

def matrix_multiply(N):
    A = np.random.randint(0, 10, (N, N))
    B = np.random.randint(0, 10, (N, N))

    start = time.time()
    C = np.dot(A, B)
    end = time.time()

    print(f"N={N}, Time: {(end - start)*1000:.3f} ms")

sizes = [200, 400, 800, 1200, 1600, 2000]

for N in sizes:
    matrix_multiply(N)