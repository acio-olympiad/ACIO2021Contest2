import os
Cases=[]
FILE_NAME="game" #game1-1.in = sub 1 of case 1
def addcase(n,t,s):
    Cases.append([n,t,s])

def SB1():
    addcase(2,1,1)
    addcase(2,2,1)
    addcase(2,3,1)
    for i in range(20):
        addcase(100-(i%2), 1+(i%3),1)

def SB2():
    for i in range(15):
        addcase(1000-(i%2), 1+(i%3),2)

def SB3():
    for i in range(10):
        addcase(10**5, 1,3)

def SB4():
    for i in range(15):
        addcase(10**5, 1+(i%3),4)


def SB5():
    for i in range(15):
        addcase(10**5, 1+(i%3),5)

def make():
    os.system("g++ tkgen.cpp -O2 -o tkgen")
    SB_COUNT=[0]*6
    for i in Cases:
        l=open("tmp.txt",'w')
        l.write("{} {} {}".format(i[0],i[1],i[2]))
        l.close()
        print("Generating",i)
        os.system("./tkgen <tmp.txt >{}{}-{}.in".format(FILE_NAME,str(i[2]),str(SB_COUNT[i[2]])))
        SB_COUNT[i[2]]+=1
SB1()
SB2()
SB3()
SB4()
SB5()
make()
