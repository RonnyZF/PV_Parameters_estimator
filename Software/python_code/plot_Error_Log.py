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

num=[]
result_fixed=[]
result_exact=[]
error=[]
#------------------------------------------------
with open('HLS_log.CSV') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        a=float(row[0])
        b=float(row[1])
        num.append(a)
        result_fixed.append(b)

for i in range(len(num)):
	result_exact.append(math.log(num[i]))

for i in range(len(num)):
	#error.append( np.log( (abs(result_exact[i]-result_fixed[i])/result_exact[i]) *100 ) )
	error.append( (abs(result_fixed[i]-result_exact[i])) / abs(result_exact[i]) *100)

with open('resultado_error_log.txt', 'w') as File:
	for i in range(len(num)):
		print(f'valor= {num[i]}\tln approx= {result_fixed[i]}\tln exact= {result_exact[i]}\t%error= {error[i]}',file=File)


#------------------------------------------------------------
fig1=plt.figure(1)
plt.plot(num[1:len(num)], result_exact[1:len(num)], 'b',label="exact",linestyle='-')
plt.plot(num[1:len(num)], result_fixed[1:len(num)], 'g',label="approx")
plt.plot(num[1:len(num)], error[1:len(num)], 'r',label="log(exact-approx/exact)")
plt.xlabel('X')
plt.ylabel('ln(X)')
plt.title('Error en aproximación de logaritmo')
plt.grid(True)
plt.savefig("error_log.png")
plt.legend()
plt.show()
