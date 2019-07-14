# -*- coding: utf-8 -*-
"""
Created on Sat Jul 13 16:35:40 2019

@author: Zarif
"""

import numpy as np
import math
import matplotlib.pyplot as plt

def next_round_hobe(table):    
    lr = len(table[:,0])   
    m = min(table[lr-1,:-1])    
    if m>=0:
        return False
    else:
        return True

def neg_idx(table):
    lr = len(table[:,0])
    m = min(table[lr-1,:-1])
    if m<=0:
        n = np.where(table[lr-1,:-1] == m)[0][0]
    else:
        n = None
    return n

def local_piv(table):
    total = []
    n = neg_idx(table)
    for i,b in zip(table[:-1,n],table[:-1,-1]):
        #print("-----------> ",i)
        if i==0:
            total.append(10000)
        elif b/i >0 and i**2>0:
            total.append(b/i)
        else:
            total.append(10000)
    index = total.index(min(total))
    return (index,n)
    
def eliminate(table,r,c):
    table[r, 0:] = table[r, 0:]/table[r][c]
    lr = len(table[:,0])
    for i in range(0,lr):
        if(i==r):
            continue
        mul = table[i][c]/table[r][c]
        table[i, 0:] = table[i, 0:] - mul* table[r, 0:]
    #print(table)
    return table
    
def solve(table,header_ara,basic_ara,f):

    ans_ara=[]
    while next_round_hobe(table):
        (r,c) = local_piv(table)
        print("R IS ",r," and C IS ",c)
        #if(r==None or c==None):
            #break
        ans_ara.append((c,r))
        table = eliminate(table,r,c)
        basic_ara[r] = header_ara[c]
        print(basic_ara)
        np.set_printoptions(formatter={'float': '{: 0.2f}'.format})
        print_in_file(table,header_ara,basic_ara,f)
        print(table)
        print("===============")

    return (ans_ara,table)

def truncate(f, n):
    '''Truncates/pads a float f to n decimal places without rounding'''
    s = '{}'.format(f)
    if 'e' in s or 'E' in s:
        return '{0:.{1}f}'.format(f, n)
    i, p, d = s.partition('.')
    return '.'.join([i, (d+'0'*n)[:n]])

def print_in_file(table,header_ara,basic_ara,f):
    
    f.write("\t")
    
    for x in header_ara:
        f.write(x+"\t")
    f.write("\n")
        
    lh = len(header_ara)
    lb = len(basic_ara)
    
    for i in range(lb):
        f.write(basic_ara[i]+"\t")
        for j in range(lh):
            f.write(str(format(table[i][j],'.2f'))+"\t")
            #f.write(truncate(table[i][j],2)+"\t")
        f.write("\n")
        
    f.write("\n")
    

def generate_matrix():
    f = open("inSimplex.txt","r")
    inp = []
    z = f.readline()
    row = 1
    col = 1
    for x in f:
        row += 1
        sp = x.split(" ")
        for y in sp:
            num = float(y)
            inp.append(num)
            #print(num)
            
    sp = z.split(" ")
    for y in sp:
        col+=1
        num = float(y)
        num = -1*num
        inp.append(num)
        #print(num)
        
    inp.append(0)
    
    inp = np.array(inp)
    inp.shape=(row,col)
    np.set_printoptions(formatter={'float': '{: 0.2f}'.format})
    #print(inp)
    ara = np.zeros((row,row+col))

    for j in range(col-1):
        ara[:,j] = inp[:,j]
    cnt = 0
    for i in range(col-1,row+col-1):
        ara[cnt,i] = 1
        cnt += 1
    ara[:,row+col-1] = inp[:,col-1]
        
    #print(ara)
    return (inp,ara,row,col)

def draw_graph(inp,row,col):
    
    yara = []
    plt.figure(1 , figsize=(16,10))
    xmaxx = 0
    ymaxx = 0
    xminn = 100000
    
    for i in range(row-1):
        if(inp[i,0]!=0):
            xmaxx = max(xmaxx,inp[i,2]/inp[i,0])
            xminn = min(xminn,inp[i,2]/inp[i,0])
        if(inp[i,1]!=0):
            ymaxx = max(ymaxx,inp[i,2]/inp[i,1])
        
    #print(xmaxx)
    x = np.linspace(0, xmaxx, 20000)
    fill_x = np.linspace(0, xminn, 20000)

    for i in range(row-1):
        if(inp[i,1]==0):
            plt.axvline(x=inp[i,2]/inp[i,0],linewidth=3,color = '#b1219d', label = "x = "+str(inp[i,2]/inp[i,0]))
            continue
        elif(inp[i,0]==0):
            #print("--------- ",inp[i,2]/inp[i,1])
            plt.axhline(y=inp[i,2]/inp[i,1],linewidth=3,color = '#30b121', label = "y = "+str(inp[i,2]/inp[i,1]))
            y = inp[i,2]/inp[i,1]
            yara.append(y)
            continue
        y = (inp[i,2]-inp[i,0]*x)/inp[i,1]
        yy = (inp[i,2]-inp[i,0]*fill_x)/inp[i,1]
        yara.append(yy)
        plt.plot(x, y,linewidth = 2,label = str(inp[i,0])+"x + "+str(inp[i,1])+" y = "+str(inp[i,2]))
    yy = x*0
    plt.plot(x, yy,linewidth = 2)
    

    plt.xlim((0, xmaxx))
    plt.ylim((0, ymaxx))
    plt.xlabel("X1")
    plt.ylabel("X2")
    plt.title("LP Maximization")
    plt.grid(color='grey',linewidth=0.5,dashes=[10,2,2,2,2,2])
        
    tt = np.minimum(yara[0],yara[1])
    for i in range(2,len(yara)):
        tt = np.minimum(tt,yara[i])
        
    #fx = np.linspace(1,2, 2000)

    plt.fill_between(fill_x, tt, yy, where=tt>yy, color='grey', alpha=0.4, hatch = '/',label = "Feasible Region")
    plt.legend(loc = 'upper right')
    #plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
    
    
if __name__ == '__main__':
    
    #ar = [[1.0,4,1,0,0,12],[1,3,0,1,0,10],[-2,-4,0,0,1,0]]
    #ar = [[4.0,3,1,0,240],[2,1,0,1,100],[-70,-50,0,0,0]]
    
    (inp,ara,row,col) = generate_matrix()
    print(ara)
    
    var_ara = ["X"+str(i) for i in range(1,col)]
    slack_ara = ["S"+str(i) for i in range(1,row)]
    slack_ara += "Z"
    header_ara = var_ara + slack_ara
    header_ara += "F"
    basic_ara = slack_ara
    
    print(header_ara)
    print(basic_ara)

    np.set_printoptions(formatter={'float': '{: 0.2f}'.format})
    f = open("outSimplex.txt","w+")
    #print(np.array(ara))
    print_in_file(ara,header_ara,basic_ara,f)
    (ans,tab) = solve(ara,header_ara,basic_ara,f)
    
    l = len(ans)
    lc = len(tab[0,:])
    lr = len(tab[:,0])
    
    #print(tab)
    
    f.write("\n")
    
    hobe = True
    mark = np.zeros(col-1)
    
    for i in range(0,l):
        (c,r) = ans[i]
        #print(c," & ",r, " ## ",col)
        if(c>=col-1):
            continue
        sum = 0
        for j in range(lr):
            sum += tab[j,c]
        #print("Sum is ",sum)
        if(sum==1):
            #print(var_ara[c]," : ",tab[r][lc-1])
            mark[c] = tab[r][lc-1]
            #f.write(var_ara[c]+" : "+truncate(tab[r][lc-1],2)+"\n")
    #print(mark)
    for i in range(col-1):
        print(var_ara[i]," : ",mark[i])
        f.write(var_ara[i]+" : "+str(format(mark[i],'.2f'))+"\n")
        #f.write(var_ara[i]+" : "+truncate(mark[i],2)+"\n")
            
    print("Maximum Value : ",tab[lr-1][lc-1])
    f.write("Maximum Value : "+str(format(tab[lr-1][lc-1],'.2f'))+"\n")
    #f.write("Maximum Value : "+truncate(tab[lr-1][lc-1],2)+"\n")
    
    if(len(var_ara)==2):
        draw_graph(inp,row,col)
        
    f.close()
    

