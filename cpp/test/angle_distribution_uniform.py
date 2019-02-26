# angle_distribution_uniform.py

import math
import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate as integrate

# Load the data files
angle_uniform_data = np.loadtxt("TestAngleDistributionUniform.dat")

# Distribution functions
angle_uniform = lambda x : 0.5*math.sin(x)

npoints = 1000
x = np.linspace(0.0,math.pi, npoints)
y = map(angle_uniform,x)

# Plot the results
plt.plot(x,y)
plt.hist(angle_uniform_data, bins=npoints, density=True)
plt.show()
