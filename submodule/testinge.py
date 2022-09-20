t=int(input())
nlist=[]
for i  in range (0,t,1):
    n=int(input())
    nlist.append(n)
for j in range (0,t,1):
    for k in range(nlist[j],0,-1):
        # if((k+1)%5!=0):
        # print("*",end="")
        # else:
        #     print("#",end="")
        print(k)
print("\n")
        