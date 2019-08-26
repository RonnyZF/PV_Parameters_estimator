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

Lambda=3.99    					#Short-Circuit current
Psi=5.1387085e-6				#Is current (saturation)
alpha=0.625					#Thermal voltage relation
V_oc=1/alpha*(math.log(Lambda/Psi))		#Open circuit voltage
V_mpp=17.4					#Maximum power point voltage
I_mpp=3.75					#Maximum power point current
P_mpp=65.25					#Maximum power 
y=math.log(Lambda)				#Short-Circuit logarithm
b=math.log(Psi)					#Is current logarithm

def InputVoltage(t):
    "This functions defines the time evolution of v"		#Vpv	
    V_cte=16.69							#Average voltage
    #print (V_cte+0.3*V_cte*math.sin(2*math.pi*100*t))   	#Print Vpv
    return V_cte+0.3*V_cte*math.sin(2*math.pi*100*t)
#------------------------------------------------

def InputCurrent(t):
	return Lambda - math.exp(alpha*InputVoltage(t)+b)


def InputVoltage_scale(t):
    "This functions defines the time evolution of v"		#Vpv	
    V_cte=16.69							#Average voltage
    return (V_cte+0.3*V_cte*math.sin(2*math.pi*100*t))/22
#------------------------------------------------

def InputCurrent_scale(t):
	return (Lambda - math.exp(alpha*InputVoltage(t)+b))/5


stoptime = 15
numpoints = 15000

t = [stoptime * float(i) / (numpoints - 1) for i in range(numpoints)]
time=np.array(t) 


signal_plot=np.vectorize(InputVoltage)
fig1=plt.figure(1)
plt.plot(time[1:200], signal_plot(time)[1:200])
plt.axis([0,0.3,0,25])
plt.xlabel('time (s)')
plt.ylabel('Voltage (V)')
plt.title('Vpv')
plt.grid(True)

time=np.array(t) #Convertimos a array para poder generar y plotear
signal_plot=np.vectorize(InputCurrent)
signal_plot=signal_plot
fig2=plt.figure(2)
plt.plot(time[1:200], signal_plot(time)[1:200])
plt.axis([0,0.3,-1,10])
plt.xlabel('time (s)')
plt.ylabel('Corrienten (I)')
plt.title('Ipv')
plt.grid(True)

time=np.array(t) #Convertimos a array para poder generar y plotear
volt_plot=np.vectorize(InputVoltage_scale)
fig3=plt.figure(3)
plt.plot(time[1:200], volt_plot(time)[1:200])
plt.axis([0,0.3,-0.5,1.5])
plt.xlabel('time (s)')
plt.ylabel('Voltage escalado (V)')
plt.title('Vpv escalado')
plt.grid(True)

time=np.array(t) #Convertimos a array para poder generar y plotear
current_plot=np.vectorize(InputCurrent_scale)
fig4=plt.figure(4)
plt.plot(time[1:200], current_plot(time)[1:200])
plt.axis([0,0.3,-0.5,1.5])
plt.xlabel('time (s)')
plt.ylabel('Corriente escalada (I)')
plt.title('Ipv escalada')
plt.grid(True)

#csv generation

volt_plot=np.vectorize(InputVoltage_scale)
current_plot=np.vectorize(InputCurrent_scale)

#with open('DATA_1msps.CSV', 'w') as csvFile:
with open('DATA.CSV', 'w') as csvFile:
    row=[]
    writer = csv.writer(csvFile)
    for i in range(len(time)):
    	row.append([time[i],current_plot(time)[i],volt_plot(time)[i]])
    	print(i)
    writer.writerows(row)
csvFile.close()

plt.show()
