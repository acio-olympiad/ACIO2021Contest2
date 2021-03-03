N=10**5
Q=0
U=10**9
L=10**9
p=30
import random
l=open("gcd.in","w")
l.write(str(N)+" "+str(Q)+"\n")
for c in range(N):
    l.write(str(random.randint(L, U))+" ")
l.write("\n")
for c in range(Q):
    l.write(str(random.randint(1,N))+" "+ str(random.randint(L, U))+"\n")
l.close()
