import numpy as np
def time_constant(r, c):
    return 1 / (2 * np.pi * r * c)

r = 10000
c = 10 * 10**(-9)
#print(f'time constant: {time_constant(r,c)}')
print(3e1 * 1e6)