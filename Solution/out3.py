P="PROTON"
N='NEUTRON'
A='ALPHA'
def valid(x,y,ui):
    if x<0 or y<0 or x>29 or y>19:
        return False
    for j in ui:
        if j[0]==x and j[1]==y :
            return False
def solve(ps: int, ns: int, pt: int, nt: int, ui):

    n,m=30,20
    v=[[False for i in range(m)] for i in range(n)]
    L = [[ps,ns]]
    Ans=[]
    P=[[False for i in range(m)] for i in range(n)]
    i=0
    while L[i][0]!=pt or L[i][1]!=nt :
        if valid(L[i][0]+1,L[i][1],ui) :
            if v[L[i][0]][L[i][1]]==False :
                v[L[i][0]][L[i][1]] = True
                P[L[i][0]+1][L[i][1]]=1
                L.append(L[i][0]+1,L[i][1])
        i+=1
    X,Y=pt,nt
    while X!=ps and Y!=ns:
        if P[X][Y]==1:
            Ans=[P]+Ans
            X=X-1
        elif P[X][Y]==2:
            Ans=[N]+Ans
            Y=Y-1
        elif P[X][Y]==3:
            Ans=[A]+Ans
            X,Y=X+2,Y+2

    return Ans

