import csv, wave, math, struct, functools, random
import numpy as np
import scipy as sp
import matplotlib.pyplot as plt
import scipy.signal as signal
import scipy.io.wavfile as wavfile
from scipy.integrate import odeint
from scipy.interpolate import interp1d
from matplotlib import rc
from numpy import array

samples=192000
time=[]
current=[]
volt=[]
LinearPV=[]
data=[]
#------------------------------------------------
with open('DATA.CSV') as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count=0
    for row in csv_reader:
        t=float(row[0])
        c=float(row[1])
        v=float(row[2])
        time.append(t)
        current.append(c*-1)
        volt.append(v*-1)

print(len(time))
time = np.arange(samples)
ipv = array(current)
vpv = array(volt)

aList=[ipv,vpv]
xArray=np.array(aList)

print(xArray)
f = "sound.wav"
print ("writing " + f)
wavfile.write(f, 192000, xArray.T)
