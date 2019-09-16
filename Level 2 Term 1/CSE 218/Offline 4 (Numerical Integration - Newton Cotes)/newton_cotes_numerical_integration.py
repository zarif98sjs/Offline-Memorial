"""
Created on Sat Aug 17 13:41:54 2019

@author: Zarif
"""

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
  
def int_by_trap(idx,data_x,data_y):
    a = data_x[idx]
    fa = data_y[idx]
    b = data_x[idx+1]
    fb = data_y[idx+1]
    val = ((b-a)*(fa+fb))/2
    plt.fill_between(data_x[idx:idx+2],data_y[idx:idx+2], color="blue", alpha=0.4, hatch = '/')
    return val

def int_by_one_three(idx,data_x,data_y):
    a = data_x[idx]
    fa = data_y[idx]
    fb = data_y[idx+1]
    c =  data_x[idx+2]
    fc = data_y[idx+2]
    val = ((c-a)*(fa+4*fb+fc))/6
    plt.fill_between(data_x[idx:idx+3],data_y[idx:idx+3], color="green", alpha=0.4, hatch = '/')
    return val

def int_by_three_eight(idx,data_x,data_y):
    a = data_x[idx]
    fa = data_y[idx]
    fb = data_y[idx+1]
    fc = data_y[idx+2]
    d =  data_x[idx+3]
    fd = data_y[idx+3]
    val = ((d-a)*(fa+3*fb+3*fc+fd))/8
    plt.fill_between(data_x[idx:idx+4],data_y[idx:idx+4], color="orange", alpha=0.4, hatch = '/')
    return val

trap = 0
s1by3 = 0
s3by8 = 0

def int_segment(n,idx,data_x,data_y):
    global trap,s1by3,s3by8
    if n==1:
        trap += 1
        return int_by_trap(idx,data_x,data_y)
    cnt = 0
    ans = 0
    if n%3 == 0:
        while(cnt<n):
            ans += int_by_three_eight(idx,data_x,data_y)
            s3by8 +=3
            idx += 3
            cnt += 3
        return ans
    if n%3 == 1:
        while(cnt<n-4):
            ans += int_by_three_eight(idx,data_x,data_y)
            s3by8 +=3
            idx += 3
            cnt += 3
        ans += int_by_one_three(idx,data_x,data_y)
        idx += 2
        ans += int_by_one_three(idx,data_x,data_y)
        s1by3 += 4
        return ans
    if n%3 == 2:
        while(cnt<n-2):
            ans += int_by_three_eight(idx,data_x,data_y)
            s3by8 +=3
            idx += 3
            cnt += 3
        ans += int_by_one_three(idx,data_x,data_y)
        s1by3 += 2
        return ans

if __name__ == '__main__':
    f = open("input.txt","r")
    data_x = []
    data_y = []
    n = int(f.readline())
    for line in f:
        temp = line.split(" ")
        temp[0] = float(temp[0])
        temp[1] = float(temp[1])
        data_x.append(temp[0])
        data_y.append(temp[1])
        
    data_x = np.array(data_x,dtype = np.float64)
    data_y = np.array(data_y,dtype = np.float64)
    
    plt.figure(1 , figsize=(16,10))
    plt.plot(data_x,data_y,color = 'purple')
    pnt = plt.scatter(data_x,data_y,s=40,color = 'purple',label = "Given Data")
    plt.grid(color='grey',linewidth=0.5,dashes=[10,2,2,2,2,2])

    eps = 1e-6
    prev = 0
    start_idx = 0
    seg = 0
    ans = 0
    for i in range(0,n-1):
        now = data_x[i]-data_x[i+1]
        if(abs(now-prev)<=eps):
            seg += 1
        else:
            if(seg!=0):
                #print("Start ------------ ",start_idx)
                #print("Segment ",seg)
                ans += int_segment(seg,start_idx,data_x,data_y)
            start_idx = i
            seg = 1
            prev = now
    #print("Start ------------ ",start_idx)  
    #print("Segment ",seg)
    ans += int_segment(seg,start_idx,data_x,data_y)
    print("Trapezoid: ",trap," intervals")
    print("1/3 rule: ",s1by3," intervals")
    print("3.8 rule: ",s3by8," intervals")
    print("Integral value: ",ans)
    blue_patch = mpatches.Patch(color='blue', label='Trapezoidal Rule',alpha=0.4, hatch = '/')
    green_patch = mpatches.Patch(color='green', label="Simpson's 1/3 Rule",alpha=0.4, hatch = '/')
    orange_patch = mpatches.Patch(color='orange', label="Simpson's 3/8 Rule",alpha=0.4, hatch = '/')
    temp = []
    temp.append(pnt)
    if(trap>0):
        temp.append(blue_patch)
    if(s1by3>0):
        temp.append(green_patch)
    if(s3by8>0):
        temp.append(orange_patch)
                
    plt.legend(handles=temp)
    plt.xlabel('Value of x')
    plt.ylabel('Value of f(x)')
    plt.title("Numerical Integration using Newton Cotes Integration Formulas")
    #plt.legend()
