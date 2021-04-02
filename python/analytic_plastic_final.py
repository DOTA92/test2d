import numpy as np
import math
import matplotlib.pyplot as plt

# material properties
E = 68.9e9
nu = 0.35
H = 0
sigma0 = 68.9e6

#Initialisation
epsm1 = np.array([0., 0., 0., 0., 0., 0.])
sigm1 = np.array([0., 0., 0., 0., 0., 0.])
ss = np.array([0., 0., 0., 0., 0., 0.])
Vid = np.array([1., 1., 1., 0., 0., 0.])

pn = 0
trsig = 0.
ori = np.array([1., 0., 0., 0., 0., 0.])
deps = 1e-5
time1 = np.arange(0, 0.01, deps)
veps = [0]
vsigma = [0]

#Decomposition
oritr = 1./3.*(ori[0] + ori[2] + ori[3])* Vid
oridev = ori - oritr

#Compute material constant
k = E/(3*(1-2*nu))
mu = E/(2*(1+nu))
#Compliance matrix
S_ = 1./E * np.array( [[1., -nu, -nu, 0., 0., 0.],
	                  [-nu, 1., -nu, 0., 0., 0.],
	                  [-nu, -nu, 1., 0., 0., 0.],
	                  [0., 0., 0., 2+2*nu, 0., 0.],
	                  [0., 0., 0., 0., 2+2*nu, 0.],
	                  [0., 0., 0., 0., 0., 2+2*nu],])

i = 1
while i < len(time1):
	ki = (time1[i] + np.matmul(np.matmul(S_,sigm1) - epsm1, ori)) / (np.matmul(np.matmul(S_,ori),ori))
	eps = ki * np.matmul(S_,ori) - np.matmul(S_,sigm1) + epsm1
	vdeps = eps - epsm1
	#decomposition
	vdepstr = 1./3.*(vdeps[0]+vdeps[1]+vdeps[2])*Vid
	vdepsdev = vdeps - vdepstr
	ss = ss + 2.*mu*vdepsdev
	sigmaeq = math.sqrt(3./2.*(ss[0]*ss[0] + ss[1]*ss[1] + ss[2]*ss[2] + 2*ss[3]*ss[3] + 2*ss[4]*ss[4] + 2*ss[5]*ss[5]))
	if (sigmaeq > (sigma0 + H*pn)):
		pn = (3*mu)/(H+3*mu)*pn + (sigmaeq - sigma0)/(H+3*mu)
		ss = (sigma0+H*pn)/sigmaeq * ss
	trsig = trsig + 3*k*(vdeps[0]+vdeps[1]+vdeps[2])
	sig = 1./3.*trsig*Vid + ss
	#print(sig)
	veps.append(eps[0])
	vsigma.append(sig[0]*1e-6)
	sigm1 = sig
	epsm1 = eps
	i = i+1

plt.plot(veps, vsigma)   
plt.ylabel('Stress (Mpa)', fontsize = 14)
plt.xlabel('Strain')
plt.show()

