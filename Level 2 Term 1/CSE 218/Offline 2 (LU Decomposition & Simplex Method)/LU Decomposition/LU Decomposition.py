# -*- coding: utf-8 -*-
"""
Created on Fri Jul 12 12:08:59 2019

@author: Zarif
"""

import numpy as np
import math

def solve(ar,b,n):
    (l,u) = forward_elim(ar,b,n)
    y = []
    x = []
    
    hobena = True
    
    for i in range(n):
        hobena = True
        for j in range(n):
            if(u[i,j]!=0):
                hobena = False
        if(hobena):
            break
    
    if(hobena):
        return(l,u,y,x,hobena)
        
    #FORWARD SUBSTITUTION
    y = forward_sub(l,b,n)
    #print(y)
    #BACKWARD SUBSTITUTION
    x = backward_sub(u,y,n)
    #print(x)
    return (l,u,y,x,hobena)
    
def forward_elim(ar,b,n):
    """ Forward Elimination results into Upper Triangle Matrix """
    loT=np.identity(n)
    for k in range(0,n):
        for row in range(k+1, n):
            mul = ar[row,k]/ar[k,k]
            #print(mul)
            ar[row, k:] = ar[row, k:] - mul* ar[k, k:]
            loT[row][k] = mul
            #print(ar)
    upT=ar
             #b[row] = b[row] - multiplier*b[k]
    
    return (loT,upT)
    
def forward_sub(LT,B,n):
    Y = np.zeros(n)
    for k in range(0,n):
        #print(loT[k, 0:k-1])
        #print("-----------")
        #print(y[0:k-1])
        #print("===========")
        Y[k] = (B[k] - np.dot(LT[k, 0:n-1] , Y[0:n-1]))/LT[k,k]
    return Y

def backward_sub(UT,B,n):
    X = np.zeros(n)
    for k in range(n-1, -1, -1):
        X[k] = (B[k] - np.dot(UT[k,k+1:],X[k+1:]))/UT[k,k]
    return X

def truncate(f, n):
    '''Truncates/pads a float f to n decimal places without rounding'''
    s = '{}'.format(f)
    if 'e' in s or 'E' in s:
        return '{0:.{1}f}'.format(f, n)
    i, p, d = s.partition('.')
    return '.'.join([i, (d+'0'*n)[:n]])
           
if __name__ == '__main__':
    
    #ar = [ [25.0,5,1] , [64,8,1] , [144,12,1] ]
    #b = [106.8,177.2,279.2]
    f = open("inLU.txt","r")
    n = int(f.readline())
    ara = [] 
    b = []
    for i in range(0,n):
        temp = f.readline()
        sp = temp.split(" ")
        for x in sp:
            num = float(x)
            ara.append(num)
    
    for i in range(0,n):
        num = f.readline()
        num = float(num)
        b.append(num)
        
    f.close()
        
    #ar = [ [2.0,5,-6,7] , [1,-3,4,5] , [4,10,-12,14] ,[7,3,-6,8] ]
    #b = [25,40,38,60]
    
    #print(truncate(1.2777777777,4))

    ara = np.array(ara);
    ara.shape=(n,n)
    b = np.array(b)
    b.shape=(n,1)
    
    
    #print(ara)
    #print(b)
    #print(ara)
    (l,u,y,x,hobena) = solve(ara,b,n)
    np.set_printoptions(formatter={'float': '{: 0.4f}'.format})

    #print(l)
    #print(u)
    #print(y)
    #print(x)
    
    
    f2 = open("outLU.txt","w+")
    
    for i in range(n):
        for j in range(n):
            #f2.write(truncate(l[i][j],4)+" ")
            f2.write(str(format(l[i][j],'.4f'))+" ")
        f2.write('\n')
    f2.write('\n')
    
    for i in range(n):
        for j in range(n):
            #f2.write(truncate(u[i][j],4)+" ")
            f2.write(str(format(u[i][j],'.4f'))+" ")
        f2.write('\n')
    f2.write('\n')
    

    if(hobena):
        f2.write("No unique solution")
    else:
        for i in range(n):
            #f2.write(truncate(y[i],4)+"\n")
            f2.write(str(format(y[i],'.4f'))+"\n")
        f2.write('\n')
        for i in range(n):
            #f2.write(truncate(x[i],4)+"\n")
            f2.write(str(format(x[i],'.4f'))+"\n")
    
    f2.close()
        
    
    


