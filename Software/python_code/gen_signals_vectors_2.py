import csv
import math
import functools
import numpy as np

Lambda=3.99                     #Short-Circuit current
Psi=5.1387085e-6                #Is current (saturation)
alpha=0.625                 #Thermal voltage relation
V_oc=1/alpha*(math.log(Lambda/Psi))     #Open circuit voltage
V_mpp=17.4                  #Maximum power point voltage
I_mpp=3.75                  #Maximum power point current
P_mpp=65.25                 #Maximum power 
y=math.log(Lambda)              #Short-Circuit logarithm
b=math.log(Psi)                 #Is current logarithm

def InputVoltage(t):
    "This functions defines the time evolution of v"        #Vpv    
    V_cte=16.69                         #Average voltage
    #print (V_cte+0.3*V_cte*math.sin(2*math.pi*100*t))      #Print Vpv
    return V_cte+0.3*V_cte*math.sin(2*math.pi*1000*t)
#------------------------------------------------

def InputCurrent(t):
    return Lambda - math.exp(alpha*InputVoltage(t)+b)

def InputVoltage_scale(t):
    "This functions defines the time evolution of v"        #Vpv    
    V_cte=16.69                         #Average voltage
    return (V_cte+0.3*V_cte*math.sin(2*math.pi*1000*t))/22
#------------------------------------------------

def InputCurrent_scale(t):
    return (Lambda - math.exp(alpha*InputVoltage(t)+b))/5

t = [0]
i=0
minutos=1
sample_rate=192000
step=1/sample_rate

n_samples=minutos*60*sample_rate
for x in range(0,n_samples):
    print(i)
    time=np.array(t) 
    V=InputVoltage_scale(time[0])
    I=InputCurrent_scale(time[0])
    inputs = range(len(time))
    volt_plot=np.vectorize(InputVoltage_scale)
    current_plot=np.vectorize(InputCurrent_scale)
    with open('DATA.CSV', 'a') as csvFile:
        row=[]
        writer = csv.writer(csvFile)
        writer.writerow([time[0],I,V])
    t[0]+=step
    i+=1
csvFile.close()
