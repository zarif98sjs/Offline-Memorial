# -*- coding: utf-8 -*-
"""
Created on Fri May 18 11:44:49 2019

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

def fpm(foo,xl,xu,es,mitr):
    
    print("========== False Position Method ========")
    
    if foo(xl)==None or foo(xu)==None:
        return
    
    if foo(xl)*foo(xu) >=0:
        print("Change the range such that func(xl)*func(xu)<0")
        return
    
    '''
    if xl<=-2 or xu>=1 :
        print("Domain Error , Choose appropriate domain for False Position Method")
        return
    '''
    ea = 1.1*es
    i=0    
    xp = 0
    while(ea>es and i<mitr):
        if (foo(xl)==None or foo(xu)==None):
            print("Invalid value")
            return
        if(foo(xl)==foo(xu)):
            print("Invalid value")
            return
        xm = xu - (foo(xu)*(xl-xu))/(foo(xl)-foo(xu))
        i+=1
        if(foo(xm)==None):
            print("Invalid value")
            return 
        T = foo(xl)*foo(xm)
        if T<0:
            xu = xm
        if T>0:
            xl = xm
        if T==0:
            ea = 0
            #print('noooooooooooo')
            break
            #return xm
        if i==1 or xm==0:
            xp = xm
            continue
        ea = abs((xm-xp)/xm)*100
        xp = xm
        #print("xp is ",xp , " and xm is ",xm)
        #print("ea is " ,ea)
         
    
    print("Aprrox x is : ",xm)
    #print("foo(x) is ",foo(xm))
    print("Relative approximation error is : ",ea,"%")
    print("Number of iteration : ",i)
    print("=========================================")
    
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
    
if __name__ == '__main__':
    
    plt.figure(figsize=(16,10))
    xa = np.arange(-0.3,0.3,0.01)
    ya = [fu(x) for x in xa]
    plt.grid(color='grey',linewidth=0.5,dashes=[10,2,2,2,2,2])
    plt.title("Graphical Model")
    plt.xlabel("Mole Fraction (x) ")
    plt.ylabel(" f(x) ")
    plt.xticks(np.arange(min(xa), max(xa)+1, 0.02))
    plt.plot(xa,ya,linewidth = 1,color = 'purple', label = "Function of mole fraction f(x)")
    plt.scatter(0.028, 0, color = "purple", label = "Estimated Root")
    
    plt.legend(loc='upper left')
    plt.show()
    
    xlo = float(input("Lower Bound for False Postion Method : "))
    xhi = float(input("Upper Bound for False Postion Method : "))
    
    fpm(fu,xlo,xhi,0.5,60)
    
    xlo = float(input("1st Guess for Secant Method : "))
    xhi = float(input("2nd Guess for Secant Method : "))
    
    secant(fu,xlo,xhi,0.5,60)
    #plt.plot(xa,ya2,linewidth = 4,color = 'green', label = 'lala')

