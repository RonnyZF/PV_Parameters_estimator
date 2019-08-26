import matplotlib.pyplot as plt
import math
import numpy as np
from scipy.integrate import odeint
import scipy.signal as signal
import matplotlib.pyplot as plt
from matplotlib import rc

#Defining some constants
e=math.exp(1)

#Parameters (same as Ph.D. thesis)

Lambda=3.99    					#Short-Circuit current
Psi=5.1387085e-6				#Is current (saturation)
alpha=0.625					#Thermal voltage relation
V_oc=1/alpha*(math.log(Lambda/Psi))		#Open circuit voltage
V_mpp=17.4					#Maximum power point voltage
I_mpp=3.75					#Maximum power point current
P_mpp=65.25					#Maximum power 
y=math.log(Lambda)				#Short-Circuit logarithm
b=math.log(Psi)					#Is current logarithm

#------------------------------------------------
#Time evolution of v
def InputVoltage(t):
    "This functions defines the time evolution of v"		#Vpv	
    V_cte=16.69							#Average voltage
    #print (V_cte+0.3*V_cte*math.sin(2*math.pi*100*t))   	#Print Vpv
    return V_cte+0.3*V_cte*math.sin(2*math.pi*100*t)
#------------------------------------------------
def InputCurrent(t):
    return Lambda - math.exp(alpha*InputVoltage(t)+b)
#------------------------------------------------
def LinearPV(t):                
    return math.log(Lambda-InputCurrent(t))

#--------Differential equation----				#Set ODE with stoptime=0.005 for initial estimation
#ODE solver parameters
abserr = 5e-8
relerr = 5e-8
#stoptime = 0.005
stoptime = 15
numpoints = 10000

# Create the time samples for the output of the ODE solver.
#Esto lo crea como una lista
t = [stoptime * float(i) / (numpoints - 1) for i in range(numpoints)]
#Differential equation
def vectorfield(x,t,p): 					#x:state variables, t:time, p:parameters
    theta1, theta2 = x 
    alpha, b, g11, g12, g21, g22 = p 				#Estimation equations
    f=[(g11*InputVoltage(t)+g12)*(LinearPV(t)-theta1*InputVoltage(t)-theta2),
       (g21*InputVoltage(t)+g22)*(LinearPV(t)-theta1*InputVoltage(t)-theta2)]
    #print (f)
    return f

#initial conditions
x1=0.55  	   						#Initial estimation of alpha 
x2=-13             						#Initial estimation of b

#Parameters for the numerical solution of the ode
g1a=0.0375
g1b=0.0625
g2a=135
g2b=121
sumg212=2*math.sqrt(g1b)*math.sqrt(g2b)
#g11=g1a+g1b							#Gamma equation for better adjustement
#g12=200+sumg212
#g21=-200
#g22=g2a+g2b

g11=0.1								#Gammas
g12=0
g21=0
g22=100

p=[alpha, b, g11, g12, g21, g22]				#parameters for ODE solver
x0=[x1,x2]

wsol = odeint(vectorfield, x0, t, args=(p,),			#wsol for ODE solver
             atol=abserr, rtol=relerr)

print(f'theta1 = {wsol[:,0]} theta2 = {wsol[:,1]}')

fig1=plt.figure(1);						#figure plots
ax=fig1.add_subplot(211)
ax.axis([0,stoptime,0.55,0.66])					#set axis
ax.set_xlabel('t [s]')
ax.set_ylabel(r'$\theta_1$')					#Theta_1 estimated
ax.plot(t,wsol[:,0],lw=2)
ax.plot([0,stoptime],[alpha, alpha],'k--',lw=2);
#with open("Theta_1.txt", "w") as text_file:			#Uncomment to print to txt file wsol(Theta_1) data
#    text_file.write("{}".format(wsol[:,0]))

ax.grid(True)
ax=fig1.add_subplot(212)
ax.axis([0,stoptime,-13.5,-11])
ax.set_xlabel('t [s]')
ax.set_ylabel(r'$\theta_2$')
ax.plot(t,wsol[:,1],lw=2)					#Theta_2 estimated
ax.plot([0,stoptime],[b, b],'k--',lw=2);
#with open("Theta_2.txt", "w") as text_file:			#Uncomment to print to txt file wsol(Theta_2) data
#    text_file.write("{}".format(wsol[:,1]))

ax.grid(True)

fig2=plt.figure(2);						#Phaseplane Theta_1 vs Theta_2
ax=fig2.add_subplot(111)
ax.axis([0.45,0.8,-15,-9])
ax.set_xlabel(r'$\theta_1$')
ax.set_ylabel(r'$\theta_2$')
ax.plot(wsol[:,0],wsol[:,1],'.b',ms=8)
plt.grid(True)
#plt.hold
plt.axis.hold=0
vv=17.4
yy=alpha*vv+b
print(yy)							#print Ipv
print(b)							#print ln(Is)
aa=np.zeros(2)
bb=np.zeros(2)							#trace line on phaseplane
aa[0]=0
aa[1]=0.8	
bb[0]=yy
bb[1]=-aa[1]*vv+yy
ax.plot(aa,bb,'-k',lw=2)
ax.plot(alpha,b,'ro',ms=8);

fig1.savefig('simulation_estimator1.png')
fig2.savefig('phaseplane_simulation_estimator1.eps')

#plt.show()

#Vamos a guardar los resultados en un par de archivos de texto

#Primero guardamos Input signal y "y"
V_cte=16.69
time=np.array(t) #Convertimos a array para poder generar y plotear
signal_plot=V_cte+0.3*V_cte*np.sin(2*np.pi*100*time)
fig3=plt.figure(3)
plt.plot(time[1:200], signal_plot[1:200])
plt.axis([0,0.3,0,25])
plt.xlabel('time (s)')
plt.ylabel('Voltage (V)')
plt.title('Vpv')
plt.grid(True)
plt.savefig("vpv.eps")
#plt.show()

time=np.array(t) #Convertimos a array para poder generar y plotear
c_plot=np.vectorize(InputCurrent)
fig4=plt.figure(4)
plt.plot(time[1:200], c_plot(time)[1:200])
plt.axis([0,0.3,-1,10])
plt.xlabel('time (s)')
plt.ylabel('Current (A)')
plt.title('Ipv')
plt.grid(True)
plt.savefig("ipv.eps")
plt.show()
