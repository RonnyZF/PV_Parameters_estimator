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

time=[]
current=[]
volt=[]
current_scaled=[]
volt_scaled=[]
LinearPV=[]
#------------------------------------------------
with open('DATA.CSV') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count=0
    for row in csv_reader:
        t=float(row[0])
        c=float(row[1])
        v=float(row[2])
        c_1=float(row[1])*5
        v_1=float(row[2])*22
        time.append(t)
        current.append(c)
        volt.append(v)
        current_scaled.append(c_1)
        volt_scaled.append(v_1)
        line_count += 1

for i in range(len(time)):
    Ig=3.99
    LinearPV.append(math.log(Ig-current[i]))
#------------------------------------------------------------
fig1=plt.figure(1)
plt.plot(time[1:len(time)], current[1:len(time)], 'b')
#plt.plot(time[1:2482], current[1:2482], 'b')
plt.axis([-0.0005,0.3,-1.5,1.5])
plt.xlabel('time (s)')
plt.ylabel('Current (A)')
plt.title('ipv scaled x 5')
plt.grid(True)
plt.savefig("ipv scaled x 5.png")

fig2=plt.figure(2)
#plt.plot(time[1:len(time)], volt[1:len(time)])
plt.plot(time[1:2482], volt[1:2482],'b')
plt.axis([-0.0005,0.3,0,1.5])
plt.xlabel('time (s)')
plt.ylabel('Volt (V)')
plt.title('Vpv scaled x 22')
plt.grid(True)
plt.savefig("vpv scaled x 22.png")

fig3=plt.figure(3)
plt.plot(time[1:len(time)], current_scaled[1:len(time)], 'b')
#plt.plot(time[1:2482], current[1:2482], 'b')
plt.axis([-0.0005,0.3,-0.5,5])
plt.xlabel('time (s)')
plt.ylabel('Current (A)')
plt.title('Ipv')
plt.grid(True)
plt.savefig("ipv.png")
plt.savefig("ipv.png")

fig4=plt.figure(4)
#plt.plot(time[1:len(time)], volt[1:len(time)])
plt.plot(time[1:2482], volt_scaled[1:2482],'b')
plt.axis([-0.0005,0.3,0,22])
plt.xlabel('time (s)')
plt.ylabel('Volt (V)')
plt.title('Vpv')
plt.grid(True)
plt.savefig("vpv.png")
plt.show()
