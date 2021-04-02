import numpy as np
import math
import matplotlib.pyplot as plt

# material properties
E = 68.9e9
nu = 0.35
H = 0
sigma0 = 68.9e6

#Initialisation
eps = np.array([0., 0., 0.])
Vid = np.array([1., 1., 0.])
trsigma = 0
ss = np.array([0., 0., 0.])
pn = 0
deps = 1.e-5
ori = np.array([1., -nu/(1-nu), 0.])
numstep = 200
veps = [0]
vsigma = [0]

#Compute material constant
k = E/(3*(1-2*nu))
mu = E/(2*(1+nu))

for i in range(numstep):
    ss = ss + 2*mu*(deps * ori)
    sigmaeq = math.sqrt(3./2.*(ss[0]*ss[0] + ss[1]*ss[1] + ss[2]*ss[2]))
    if (sigmaeq > (sigma0 + H*pn)):
        pn = (3*mu)/(H+3*mu)*pn + (sigmaeq - sigma0)/(H+3*mu)
        ss = (sigma0*pn)/sigmaeq * ss
    trsigma = trsigma + 3*k*deps
    sigma = 1./3.*trsigma*Vid + ss
    print(sigma)
    veps.append(deps*(i+1))
    vsigma.append(sigma[0]*1e-6)

plt.plot(veps, vsigma)   
plt.show()
