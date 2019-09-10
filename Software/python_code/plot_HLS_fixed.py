import csv
import math
import functools
import numpy as np
import scipy as sp
import matplotlib.pyplot as plt
import scipy.signal as signal
from scipy.integrate import odeint
from scipy.interpolate import interp1d
from matplotlib import rc

#Parameters (same as Ph.D. thesis)

Lambda=3.99                     #Short-Circuit current
Psi=5.1387085e-6                #Is current (saturation)
alpha=0.625                 #Thermal voltage relation
V_oc=1/alpha*(math.log(Lambda/Psi))     #Open circuit voltage
V_mpp=17.4                  #Maximum power point voltage
I_mpp=3.75                  #Maximum power point current
P_mpp=65.25                 #Maximum power 
y=math.log(Lambda)              #Short-Circuit logarithm
b=math.log(Psi)                 #Is current logarithm


time=[]
theta1=[]
theta2=[]
#------------------------------------------------
with open('HLS_fixed.CSV') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count=0
    for row in csv_reader:
        a=float(row[0])
        b=float(row[1])
        theta1.append(a)
        theta2.append(b)
        line_count += 1

stoptime = 15
numpoints = len(theta1)
t = [stoptime * float(i) / (numpoints - 1) for i in range(numpoints)]
#------------------------------------------------------------
fig1=plt.figure(1);                      #figure plots
ax=fig1.add_subplot(211)
ax.axis([0,stoptime,0.55,0.66])                 #set axis
ax.set_xlabel('t [s]')
ax.set_ylabel(r'$\theta_1$')                    #Theta_1 estimated
ax.plot(t,theta1,lw=2)
ax.plot([0,stoptime],[alpha, alpha],'k--',lw=2);
ax.grid(True)

ax=fig1.add_subplot(212)
ax.axis([0,stoptime,-13.5,-11])
ax.set_xlabel('t [s]')
ax.set_ylabel(r'$\theta_2$')
ax.plot(t,theta2,lw=2)                   #Theta_2 estimated
ax.plot([0,stoptime],[b, b],'k--',lw=2);
ax.grid(True)
plt.savefig("theta1_theta2_estimadas_HLS_fixed.png")

fig2=plt.figure(2);                     #Phaseplane Theta_1 vs Theta_2
ax=fig2.add_subplot(111)
ax.axis([0.45,0.8,-15,-9])
ax.set_xlabel(r'$\theta_1$')
ax.set_ylabel(r'$\theta_2$')
ax.plot(theta1,theta2,'.b',ms=8)
plt.grid(True)
#plt.hold
plt.axis.hold=0
vv=17.4
yy=alpha*vv+b
print(yy)                           #print Ipv
print(b)                            #print ln(Is)
aa=np.zeros(2)
bb=np.zeros(2)                          #trace line on phaseplane
aa[0]=0
aa[1]=0.8   
bb[0]=yy
bb[1]=-aa[1]*vv+yy
ax.plot(aa,bb,'-k',lw=2)
ax.plot(alpha,b,'ro',ms=8);
plt.savefig("theta1_theta2_phaseplane_HLS_fixed.png")

plt.show()
