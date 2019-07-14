# -*- coding: utf-8 -*-
"""
Created on Fri May 17 10:19:27 2019

@author: Zarif
"""
import numpy as np
import math
from matplotlib import pyplot as plt

def lnapprox(x,itr):
    ans = 0.0
    temp = 1.0
    sign = 1
    for i in range(itr):
        temp *= x
        cur = (temp)/(i+1)
        ans = ans + sign*cur
        sign = sign*-1
    return ans

if __name__ == '__main__':
    
    x = float(input("Value of x : "))
    it = int(input("Number of iteration : "))
    print("Approximation of ln( 1+",x,") is : ", lnapprox(x,it))
    
    plt.figure(1 , figsize=(16,10))
    
    xara = np.arange(-0.9,1.1,0.1)
    yara = np.log(1+xara)
    
    plt.xticks(np.arange(min(xara), max(xara)+1, 0.1))
    plt.plot(xara,yara,linewidth = 4,color = 'purple', label = 'ln(1+x)')
    plt.grid(color='grey',linewidth=0.5,dashes=[10,2,2,2,2,2])
    plt.scatter(xara,yara,linewidth = 5,color = 'purple')
    
    iteration = [1,3,5,20,50]
    ls = []
    for i in range(5):
        y = [lnapprox(x,iteration[i]) for x in xara]
        ls.append(y)
    
    plt.plot(xara,ls[0],linewidth = 3,color = 'red', label = '1 iteration')
    plt.plot(xara,ls[1],linewidth = 3,color = 'green', label = '3 iteration')
    plt.plot(xara,ls[2],linewidth = 3,color = 'orange', label = '5 iteration')
    plt.plot(xara,ls[3],linewidth = 3,color = '#5dade2', label = '20 iteration')
    plt.plot(xara,ls[4],linewidth = 3,color = '#f1948a', label = '50 iteration')
             
    plt.xlabel('Value of x ')
    plt.ylabel('Value of ln(1+x) ')
             
    plt.legend()
    plt.show()
    
    plt.figure(2 , figsize=(16,10))
   
    yer = []     
    vcurr = lnapprox(0.5,1)
    
    for i in range(1,50):
        vprev = vcurr
        vcurr = lnapprox(0.5,i+1)
        reler = (vcurr-vprev)/vcurr
        yer.append(abs(reler)*100)
        
    xerr = np.arange(2,51,1)   
    plt.grid(color='grey',linewidth=0.5,dashes=[10,2,2,2,2,2])
    plt.xticks(np.arange(0, max(xerr)+1, 5))
    plt.plot(xerr,yer,linewidth = 4,color = '#5dade2', label = 'rel approx er')
             
    plt.xlabel('Number of iterations ')
    plt.ylabel('Relative approx. error ')         
             
    plt.legend()
    plt.show()
