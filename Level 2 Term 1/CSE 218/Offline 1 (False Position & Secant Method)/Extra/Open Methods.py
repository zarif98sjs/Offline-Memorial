# -*- coding: utf-8 -*-
"""
Created on Sat Jun 15 20:03:19 2019

@author: Zarif
"""
import numpy as np
import math
from matplotlib import pyplot as plt

def fu(a,pt=3,k=.05):
    if (a==1 or a<=-2):
        print("Invalid input for x = ",a)
        return None
    q = (a*1.0)/(1-a)
    w = math.sqrt((2.0*pt)/(2+a))
    val = q*w-k
    return val

def food(f,a,h=0.01):
    return (f(a + h) - f(a - h))/(2*h)

def secant(foo,x1,x2,es,mitr):
    
    print("============ Secant Method ==============")
    
    if foo(x1)==None or foo(x2)==None:
        return
    
    '''
    if x1<=-2 or x2>=1 :
        print("Domain Error , Choose appropriate domain for Secant Method")
        return
    '''
    ea = 1.1*es
    i=0    
    #xp = 0
    while(ea>es and i<mitr):
        if (foo(x1)==None or foo(x2)==None):
            print("Invalid value")
            return
        if(foo(x1)==foo(x2)):
            print("Invalid value")
            return
        xm = x2 - ((x1-x2)/(foo(x1)-foo(x2)))*foo(x2)
        i+=1
        if i==1 or xm==0:
            x1 = x2
            x2 = xm 
            continue
        ea = abs((xm-x2)/xm)*100
        x1 = x2
        x2 = xm 
        #print("xp is ",xp , " and xm is ",xm)
        #print("ea is " ,ea)
         
    print("Aprrox x is : ",xm)
    #print("foo(x) is ",foo(xm))
    print("Relative approximation error is : ",ea,"%")
    print("Number of iteration : ",i)
    print("=========================================")

def new_raph(foo,x1,x2,es,mitr):
    
    print("============ Newton Raphson Method ==============")
    
    if foo(x1)==None or foo(x2)==None:
        return
    
    '''
    if x1<=-2 or x2>=1 :
        print("Domain Error , Choose appropriate domain for Secant Method")
        return
    '''
    ea = 1.1*es
    i=0    
    #xp = 0
    while(ea>es and i<mitr):
        if (foo(x1)==None or foo(x2)==None):
            print("Invalid value")
            return
        if(foo(x1)==foo(x2)):
            print("Invalid value")
            return
        xm = x1 - foo(x1)/food(foo,x1)
        i+=1
        if i==1 or xm==0:
            x1 = xm
            continue
        ea = abs((xm-x1)/xm)*100
        x1 = xm
        #print("xp is ",xp , " and xm is ",xm)
        #print("ea is " ,ea)
         
    print("Aprrox x is : ",xm)
    #print("foo(x) is ",foo(xm))
    print("Relative approximation error is : ",ea,"%")
    print("Number of iteration : ",i)
    print("=========================================")

    
if __name__ == '__main__':
    
    plt.figure(figsize=(10,8))
    xa = np.arange(-0.3,0.3,0.01)
    ya = [fu(x) for x in xa]
    plt.grid(color='grey',linewidth=0.5,dashes=[10,2,2,2,2,2])
    plt.title("Graphical Model")
    plt.xlabel("Mole Fraction (x) ")
    plt.ylabel(" f(x) ")
    #plt.xticks(np.arange(min(xa), max(xa)+1, 0.02))
    plt.plot(xa,ya,linewidth = 1,color = 'purple', label = "Function of mole fraction f(x)")
    plt.scatter(0.028, 0, color = "purple", label = "Estimated Root")
    
    plt.legend(loc='upper left')
    plt.show()
    
    xlo = -0.9
    xhi = 0.9
    
    #xlo = float(input("Lower Bound for False Postion Method : "))
    #xhi = float(input("Upper Bound for False Postion Method : "))
    
    secant(fu,xlo,xhi,0.5,100)
    
    #xlo = float(input("1st Guess for Bisection Method : "))
    #xhi = float(input("2nd Guess for Bisection Method : "))
    
    new_raph(fu,xlo,xhi,0.5,60)
    
    #plt.plot(xa,ya2,linewidth = 4,color = 'green', label = 'lala')

