from joblib import Parallel, delayed
import multiprocessing
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


stoptime = 30#15
numpoints = 3750000#1875000
num_cores = multiprocessing.cpu_count()

t = [stoptime * float(i) / (numpoints - 1) for i in range(numpoints)]
time=np.array(t) 
inputs = range(len(time))
volt_plot=np.vectorize(InputVoltage_scale)
current_plot=np.vectorize(InputCurrent_scale)

print(len(time))
print(num_cores)

V=Parallel(n_jobs=num_cores)((delayed(InputVoltage_scale)(time[i])) for i in inputs)
I=Parallel(n_jobs=num_cores)((delayed(InputCurrent_scale)(time[i])) for i in inputs)
volt_plot=np.array(V) 
current_plot=np.array(I) 


with open('DATA.CSV', 'w') as csvFile:
    row=[]
    writer = csv.writer(csvFile)
    for i in range(len(time)):
    	row.append([time[i],current_plot[i],volt_plot[i]])
    	print(i)
    writer.writerows(row)
csvFile.close()
