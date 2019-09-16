# -*- coding: utf-8 -*-
"""
Created on Sun Jul 21 20:17:38 2019

@author: Zarif
"""
import numpy as np
import math
import matplotlib.pyplot as plt

def poly_reg(n,data_x,data_y,r_type):
    xara =[]
    bara = []
    for i in range(1,2*r_type+1):
        temp_x = data_x**i
        xara.append(temp_x)

    for i in range(r_type+1):
        temp_b = (data_x**i)*(data_y)
        #print(temp_b)
        bara.append(temp_b)
        
    sum_xara = []
    sum_xara.append(n)
    for i in range(0,2*r_type):
        t_sum = np.sum(xara[i], dtype = np.float64)
        #print(t_sum)
        sum_xara.append(t_sum)
        
    A = []
    B = []
    
    for i in range(r_type+1):
        t_sum = np.sum(bara[i],dtype = np.float64)
        #print(t_sum)
        B.append(t_sum)
        
    B = np.array(B)
    
    for i in range(r_type+1):
        for j in range(i,i+r_type+1):
            A.append(sum_xara[j])
            
    A = np.array(A)
    A.shape = (r_type+1,r_type+1)
    #print(A)
    #print(B)
    
    sumy = np.sum(data_y,dtype = np.float64)
    avgy = sumy/n
    #sprint(avgy)
    var_ara = ["a"+str(i) for i in range(0,r_type+1)]
    #var_ara_2 = ["x^"+str(i) for i in range(0,r_type+1)]
    
    res = np.linalg.solve(A,B)
    #print(res)
    
    print("Order ",r_type," Regression")
    for i in range(0,r_type+1):
        print(var_ara[i]," = ",res[i])
    #print(np.amin(data_x))
    #print(np.amax(data_x))
    x_min = np.amin(data_x)
    x_max = np.amax(data_x)
    xx = np.linspace(x_min, x_max, 500)
    yy = np.zeros(xx.shape)
    calc_y = np.zeros(data_x.shape)
    #print(yy)
    for i in range(r_type+1):
        yy += res[i]* (xx**i)
        calc_y += res[i]* (data_x**i)
        #print(yy)

    #plt.scatter(xx,yy,s=5)
    plt.plot(xx,yy,linewidth=2.5,label='Order '+str(r_type))
    
    st = 0
    sr = 0
    for dy in data_y:
        st += (dy-avgy)**2
    for i in range(n):
        sr += (data_y[i]-calc_y[i])**2
        
    #print("St ",st)
    #print("Sr ",sr)
    r = np.sqrt(1-sr/st)
    print("Regression Co-efficient (R) is ",r)
    

if __name__ == '__main__':
    f = open("data.txt","r")
    data_x = []
    data_y = []
    n = 0
    for line in f:
        temp = line.split(" ")
        temp[0] = float(temp[0])
        temp[1] = float(temp[1])
        data_x.append(temp[0])
        data_y.append(temp[1])
        n+=1
        
    data_x = np.array(data_x)
    data_y = np.array(data_y)
    np.set_printoptions(formatter={'float': '{: 0.9f}'.format})
    #print(n)
    #print(data_x)
    plt.figure(1 , figsize=(16,10))
    plt.scatter(data_x,data_y,s=5,color = 'purple')
    plt.grid(color='grey',linewidth=0.5,dashes=[10,2,2,2,2,2])
    poly_reg(n,data_x,data_y,1)
    poly_reg(n,data_x,data_y,2)
    poly_reg(n,data_x,data_y,3)
    plt.legend()
    plt.title("Curve Fitting")
    #create_matrix(n,data_x,data_y,6)

    #print("----------------------------------------")
    #print(data_y)
            