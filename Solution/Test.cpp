#include"Headers/My_Headers.hpp"
using namespace std;
/// @brief Print a set of points in a way that is executable with Python3
/// @param P the set of points
/// @param id Used to distinguish the arrays in python
void Print_Points(vector<pair<ld,ld> > P,ld id=0){
    if(id==0)
    id=rand();
    cout<<"X"<<id<<"=[";
    for(int i=0;i<P.size();i++){
        cout<<P[i].F<<",";
    }
    cout<<"]\nY"<<id<<"=[";
    for(int i=0;i<P.size();i++){
        cout<<P[i].S<<",";
    }
    cout<<"]\n";
    cout<<"plt.plot(X"<<id<<",Y"<<id<<")\n";
}
/// @brief Used to draw the arcs
/// @param P The set of points where the arc will be added
/// @param A the starting point of the arc
/// @param ang the staring angle of the arc
/// @param B the ending point of the arc
/// @param C the circle corresponding to the arc
/// @param n the number of points to be added from this arc
void Add_pts(vector<pair<ld,ld> > &P,pair<ld,ld> A,ld ang,pair<ld,ld> B,Circle C,ll n=10){
    ld ang2=Angle_from_Circle(C,B,A,ang);
    for(ld i=0;i<=n;i++){
        pair<ld,ld> temp;
        temp.F=A.F*(i/n)+B.F*(1-i/n)-C.O.F;
        temp.S=A.F*(i/n)+B.F*(1-i/n)-C.O.S;
        ld t=norm(temp);
        if(t==0)continue;
        ld k=C.r/t;
        temp.F*=k;
        temp.S*=k;
        temp.F+=C.O.F;
        temp.S+=C.O.S;
       // cout<<i<<endl;
        ld ang1=Angle_from_Circle(C,temp,A,ang);
        bool inclu=true;
        if(ang<=ang2){
            if(ang1<ang||ang1>ang2)inclu=false;
        }else{
            if(ang1<ang&&ang1>ang2)inclu=false;
        }
        if(!inclu){
            temp.F-=C.O.F;
            temp.S-=C.O.S;
            temp.F*=-1;
            temp.S*=-1;
            temp.F+=C.O.F;
            temp.S+=C.O.S;
        }
        P.pb(temp);
    }
}
int main(){

    freopen("out2.txt","r",stdin);
    freopen("out3.py","w",stdout);
    cout<<"import matplotlib.pyplot as plt\n";
    vector<pair<ld,ld> > Points;
    vector<Circle > C;
    vector<ld> Ang;
    ld a,b,c,x=0,y,r;
    while(x!=-1){
        cin>>a>>b>>c>>x>>y>>r;
        if(x==-1)break;
        Points.pb(mk(a,b));
        Circle temp;
        temp.O=mk(x,y);
        temp.r=r;
        C.pb(temp);
        Ang.pb(c);
    }
    vector<pair<ld,ld> > P;
    for(int i=0;i<Points.size()-1;i++){
        Add_pts(P,Points[i],Ang[i],Points[i+1],C[i]);
    }
    Print_Points(P);
    Print_Points(Points,1);
    cout<<"plt.show()"<<endl;
}
