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

alpha=0.625                 #Thermal voltage relation
Psi=5.1387085e-6                #Is current (saturation)
b=math.log(Psi)                 #Is current logarithm

GAMMA11 = 0.1
GAMMA12 =0
GAMMA21 =0
GAMMA22 = 100
INIT_ALPHA = 0.55
INIT_BETA = -13.0
IG=3.99
#T_SAMPLING=100e-6
T_SAMPLING=1e-3
stoptime = 15

time=[]
Ipv=[]
Vpv=[]
p_1=[]
p_2=[]
LinearPV=[]
#------------------------------------------------
with open('DATA.CSV') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count=0
    for row in csv_reader:
        t=float(row[0])
        c=float(row[1])
        v=float(row[2])
        time.append(t)
        Ipv.append(c)
        Vpv.append(v)
        line_count += 1

#------------------------------------------------------------
PAST_BETA=0
PAST_ALPHA=0

for i in range(len(time)):
#for i in range(0,250):
    #print(i)
    #print(f'I = {Ipv[i]}  V = {Vpv[i]}')
    I=Ipv[i]*5
    V=Vpv[i]*22
    #print(f'I esc = {I}  V esc = {V}')
    y=math.log(IG-I)
    #print(f'ln(y-ipv) {y}')
    theta1=((GAMMA11*V+GAMMA12)*(y-(V*INIT_ALPHA)-INIT_BETA))*T_SAMPLING+INIT_ALPHA
    theta2=((GAMMA21*V+GAMMA22)*(y-(V*INIT_ALPHA)-INIT_BETA))*T_SAMPLING+INIT_BETA
    #print(f' theta 1 = {theta1}  theta 2 = {theta2}\n\n')
    INIT_ALPHA=theta1
    INIT_BETA=theta2

    p_1.append(theta1)
    p_2.append(theta2)

#------------------------------------------------------------
fig1=plt.figure(1)
plt.plot(time[1:len(time)], Ipv[1:len(time)], 'b')
plt.axis([-0.0005,0.3,-1.5,1.5])
plt.xlabel('time (s)')
plt.ylabel('Current (A)')
plt.title('Ipv')
plt.grid(True)

fig2=plt.figure(2)
plt.plot(time[1:2482], Vpv[1:2482],'b')
plt.axis([-0.0005,0.3,-1.5,1.5])
plt.xlabel('time (s)')
plt.ylabel('Volt (V)')
plt.title('Vpv')
plt.grid(True)

fig3=plt.figure(3);                      #figure plots
ax=fig3.add_subplot(211)
ax.axis([0,stoptime,0.55,0.66])                 #set axis
ax.set_xlabel('t [s]')
ax.set_ylabel(r'$\theta_1$')                    #Theta_1 estimated
ax.plot(time,p_1,lw=2)
ax.plot([0,stoptime],[alpha, alpha],'k--',lw=2);
ax.grid(True)

ax=fig3.add_subplot(212)
ax.axis([0,stoptime,-13.5,-11])
ax.set_xlabel('t [s]')
ax.set_ylabel(r'$\theta_2$')
ax.plot(time,p_2,lw=2)                   #Theta_2 estimated
ax.plot([0,stoptime],[b, b],'k--',lw=2);
ax.grid(True)
plt.savefig("theta1_theta2_estimadas_euler_python.png")

fig4=plt.figure(4);                     #Phaseplane Theta_1 vs Theta_2
ax=fig4.add_subplot(111)
ax.axis([0.45,0.8,-15,-9])
ax.set_xlabel(r'$\theta_1$')
ax.set_ylabel(r'$\theta_2$')
ax.plot(p_1,p_2,'.b',ms=8)
plt.grid(True)
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
plt.savefig("theta1_theta2_phaseplane_euler_python.png")
plt.show()

with open('resultado_euler.CSV', 'w') as csvFile:
    row=[]
    writer = csv.writer(csvFile)
    for i in range(len(time)):
        row.append([p_1[i],p_2[i]])
    writer.writerows(row)
csvFile.close()
