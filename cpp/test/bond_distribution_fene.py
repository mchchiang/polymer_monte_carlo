# bond_distribution_fene.py

import math
import numpy as np
import matplotlib.pyplot as plt
import scipy.integrate as integrate

# Load the data files
bond_fene_data = np.loadtxt("TestBondDistributionFENE.dat")

# Distribution functions
e = 1.0
s = 1.0
k = 30.0
r0 = 1.6
buf = 1e-5

_bond_fene = lambda x :x*x*math.exp(-(4.0*e*((s/x)**12-(s/x)**6+0.25)-0.5*k*r0**2*math.log(1-(x/r0)**2)))

bond_fene_int = integrate.quad(_bond_fene, 0.0+buf, r0-buf)
bond_fene = lambda x : _bond_fene(x) / bond_fene_int[0]

npoints = 1000
x = np.linspace(0.0+buf,1.6-buf, npoints)
y = map(bond_fene,x)

# Plot the results
plt.plot(x,y)
plt.hist(bond_fene_data, bins=npoints, density=True)
plt.show()
