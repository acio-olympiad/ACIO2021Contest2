"""
type 1: partition into intersecting windows [1,k], [a+1,k+a],[2a+1,k+2a] ...
    and load some segments into each window randomly

    In general we can define a f(k,a,l,n) load:
        -L intervals (or some number of things per interval)
        -shift of interval of a
        -length of interval k
        -n things per group
weights are chosen arbitarily

K = 1, 2, 10, 25, 100 are options [former 2 only for subtasks 3,4]

l small: very dense e.g l = 1,2,3 (with n*l fixed)
l medium: l = N/x for x = 25 ... 100
l = large: l = N/x for x = 1 ... 5

shift: a = medium (k/3 ... k/2)
        a = large: k+1 (buckets disjoint)

length of interval: k = 1 (subtask 1 only)
                    k = 20 (k small, for subtask 2)
                    k = 30000 (for all other subtasks)

In all,
6 cases subtask 1
12 cases subtask 2 (k = 20)
12 cases subtask 3 (k = 30000)
6 cases sub 4
12 cases sub 5
24 cases sub 6

+1 min case + 2 samples = 87 cases
"""
maxK = 20
import random, os
random.seed(389472591)
Cases=[]
random.seed(12342056769789666)
def addcase(n,k,a,l,K,sb):
    Cases.append([n,k,a,l,K,random.randint(0,69696969),sb])

def SB1():
    #min case
    addcase(1,1,69,1,1,1)

    MAXN = 5 * 10**4
    #random cases
    for i in range(6):
        x = random.randint(300,600)
        addcase(x, 1,1000,MAXN//x,random.randint(1,maxK),1)


def SB2():
    MAXN = 300
    for i in range(12):
        x = random.randint(10,20)
        addcase(x, 20, random.randint(6,15),MAXN//x, random.randint(5,maxK),2)

def SB3():
    MAXN = 300
    for i in range(12):
        x = random.randint(10,20)
        addcase(x, 100000, random.randint(100000//3, 150000),MAXN//x, random.randint(5,maxK),3)

def SB4():
    #K = 1
    MAXN = 5 * 10**4
    for i in range(3):
        #1 group
        addcase(MAXN, 10**9, 69, 1, 1,4)

    for i in range(5):
        #2 - 10 groups
        grp = random.randint(2,10)
        addcase(MAXN//grp, 10**7, 5*10**6, grp, 1,4)

    for i in range(2):
        #many isolated groups
        grp = random.randint(1000,2000)
        addcase(MAXN//grp, 10**5, 10**5+1, grp, 1,4)

def SB5():
    #K = 2
    MAXN = 5 * 10**4
    for i in range(3):
        #1 group
        addcase(MAXN, 10**9, 69, 1, 2,5)

    for i in range(5):
        #2 - 10 groups
        grp = random.randint(2,10)
        addcase(MAXN//grp, 10**7, 5*10**6, grp, 2,5)

    for i in range(2):
        #many isolated groups
        grp = random.randint(1000,2000)
        addcase(MAXN//grp, 10**5, 10**5+1, grp, 2,5)

def SB6():
    MAXN = 5 * 10**4
    k = 10**5 #size of one group
    for i in range(5):
        for gtype in [0,1]: #0 means medium number of groups, 1 means large
            for ltype in [0,1]: #0 means semidense, 1 means dense
                num_per_group = 0
                phase = 0
                length = 10**5
                if gtype == 1:
                    num_per_group = random.randint(20,200)
                else:
                    num_per_group = random.randint(2000, 4000)


                if ltype == 0:
                    phase = random.randint(33333,50000)
                else:
                    phase = random.randint(90000,15*10**4)
                addcase(num_per_group, length, phase, MAXN//num_per_group, random.randint(5,maxK),6)
 
def make():
    FILE_NAME="stab"
    os.system("g++ tkgen.cpp -O2 -o Tkgen")
    SB_COUNT=[0]*10
    for i in Cases:
        l=open("tmp.txt",'w')
        l.write(" ".join([str(c) for c in i[:-1]]))
        l.close()
        print("Generating",i)
        os.system("./Tkgen <tmp.txt >{}{}-{}.in".format(FILE_NAME,str(i[-1]),str(SB_COUNT[i[-1]])))
        SB_COUNT[i[-1]]+=1
        print("./Tkgen <tmp.txt >{}{}-{}.in".format(FILE_NAME,str(i[-1]),str(SB_COUNT[i[-1]])))

SB1()
SB2()
SB3()
SB4()
SB5()
SB6()
make()
