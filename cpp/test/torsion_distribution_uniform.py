# torsion_distribution_uniform.py

import math
import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate as integrate

# Load the data files
torsion_uniform_data = np.loadtxt("TestTorsionDistributionUniform.dat")

# Distribution functions
torsion_uniform = lambda x : 1.0/(2.0*math.pi)

npoints = 1000
x = np.linspace(0.0, 2.0*math.pi, npoints)
y = map(torsion_uniform,x)

# Plot the results
plt.plot(x,y)
plt.hist(torsion_uniform_data, bins=npoints, density=True)
plt.show()
