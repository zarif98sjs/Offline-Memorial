# -*- coding: utf-8 -*-
"""
Created on Sat Jun 15 19:49:09 2019

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
    
def mod_fpm(foo,xl,xu,es,mitr):
    
    print("========== MOdified False Position Method ========")
    
    fl = foo(xl)
    fu = foo(xu)
    
    if fl==None or fu==None:
        return
    
    if fl*fu >=0:
        print("Change the range such that func(xl)*func(xu)<0")
        return
    
    '''
    if xl<=-2 or xu>=1 :
        print("Domain Error , Choose appropriate domain for False Position Method")
        return
    '''
    ea = 1.1*es
    i=0 ; il = 0 ;iu = 0   
    xp = 0
    while(ea>es and i<mitr):
        if (fl==None or fu==None):
            print("Invalid value")
            return
        if(fl==fu):
            print("Invalid value")
            return
        xm = xu - (fu*(xl-xu))/(fl-fu)
        i+=1
        if(foo(xm)==None):
            print("Invalid value")
            return 
        T = fl*foo(xm)
        if T<0:
            xu = xm
            fu = foo(xu)
            iu = 0
            il += 1
            if(il>=2):
                fl = fl/2
        if T>0:
            xl = xm
            fl = foo(xl)
            il = 0
            iu += 1
            if(iu>=2):
                fu = fu/2
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

def bisection(foo,xl,xu,es,mitr):
    
    print("========== Bisection Method ========")
    
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
        xm = (xl+xu)/2
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
    
    fpm(fu,xlo,xhi,0.5,100)
    mod_fpm(fu,xlo,xhi,0.5,100)
    
    #xlo = float(input("1st Guess for Bisection Method : "))
    #xhi = float(input("2nd Guess for Bisection Method : "))
    
    bisection(fu,xlo,xhi,0.5,60)
    
    #plt.plot(xa,ya2,linewidth = 4,color = 'green', label = 'lala')

