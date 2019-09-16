# -*- coding: utf-8 -*-
"""
Created on Wed Aug 28 11:29:17 2019

@author: Zarif
"""
import numpy as np
import math
import matplotlib.pyplot as plt

y0 = 4 

def f(x,y):
    return ((x+20*y)*math.sin(x*y))

def Euler(h):
    xara = np.arange(0,10.0001,h)
    yara = []
    yprev = y0
    yara.append(yprev)
    for idx in range(1,xara.size):
        x = xara[idx-1]
        yprev = (yprev + f(x,yprev)*h)
        yara.append(yprev)
    yara = np.array(yara)
    plt.plot(xara,yara,label="Euler's Method (Stepsize : "+str(h)+" )")
    #plt.scatter(xara,yara)
    
def RK2ndOrder(a1,a2,p,q,h,lab):
    xara = np.arange(0,10.0001,h)
    yara = []
    yprev = y0
    yara.append(yprev)
    for idx in range(1,xara.size):
        x = xara[idx-1]
        k1 = f(x,yprev)
        k2 = f(x+p*h, yprev +q*k1*h)
        yprev = yprev + ((a1*k1+a2*k2)*h)
        yara.append(yprev)
        idx+=1  
    yara = np.array(yara)
    plt.plot(xara,yara,label=lab+str(h)+" )")
    #plt.scatter(xara,yara)
    
def RK4thOrder(h):
    xara = np.arange(0,10.0001,h)
    yara = []
    yprev = y0
    yara.append(yprev)
    for idx in range(1,xara.size):
        x = xara[idx-1]
        k1 = f(x,yprev)
        k2 = f(x +0.5*h, yprev +0.5*k1*h)
        k3 = f(x +0.5*h, yprev +0.5*k2*h)
        k4 = f(xara[idx],yprev+k3*h)
        yprev = yprev + (k1+2*k2+2*k3+k4)*h*(1/6)
        yara.append(yprev)
    yara = np.array(yara)
    plt.plot(xara,yara,label="4th Order RK Method (Stepsize : "+str(h)+" )")
    #plt.scatter(xara,yara,s=3)
    
def Heun(h):
    RK2ndOrder(0.5,0.5,1,1,h,"Heun's Method (Stepsize : ")
def MidPoint(h):
    RK2ndOrder(0,1,0.5,0.5,h,"MidPoint Method (Stepsize : ")
def Ralston(h):
    RK2ndOrder(1/3,2/3,3/4,3/4,h,"Ralston's Method (Stepsize : ")
    
if __name__ == '__main__':
    
    hara = [0.01,0.05,0.1,0.5]
    func_list = [Euler,Heun,MidPoint,Ralston,RK4thOrder]
    lab = ["Euler's Method" ,"Heun's Method","MidPoint Method","Ralston's Method", "4th Order RK Method"]
    
    for i in range(0,4):
        plt.figure(i+1 , figsize=(16,10))
        plt.grid(color='grey',linewidth=0.5,dashes=[10,2,2,2,2,2])
        for ff in func_list:
            ff(hara[i])
        plt.title("Graph for stepsize "+str(hara[i]))
        plt.xlabel("Value of x")
        plt.ylabel("Value of y")
        plt.legend()
        #plt.savefig("Graph for stepsize "+str(hara[i])+".jpeg")

    for i in range(0,5):
        plt.figure(i+5 , figsize=(16,10))
        plt.grid(color='grey',linewidth=0.5,dashes=[10,2,2,2,2,2])
        for hh in hara:
            ff = func_list[i]
            ff(hh)
        plt.title(lab[i])
        plt.xlabel("Value of x")
        plt.ylabel("Value of y")
        plt.legend()
        #plt.savefig(lab[i]+".jpeg")

