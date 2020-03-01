# Enter your code here. Read input from STDIN. Print output to STDOUT
from sys import stdin

n= int(stdin.readline())
x= stdin.readline().split(' ')
x= [float(c) for c in x]
suma=0
for i in range(n):
    suma+= x[i]
mu=suma/n
suma=0
for i in range(n):
    suma+= (x[i]-mu)**2    
print(round((suma/n)**0.5,1))
