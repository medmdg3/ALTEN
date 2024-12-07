#include "Best_Segment.hpp"
using namespace std;
#define pb(a) push_back(a)
#define mk(a,b) make_pair(a,b)
#define F first
#define S second
#define V vector
#define sz() size()
typedef long long ll;
typedef long double ld;

const ld Pi=3.1415926535;
ld prod_Scalaire(pair<ld,ld> A,pair<ld,ld> B){
    return A.F*B.F+A.S*B.S;
}
ld get_Distance(pair<ld,ld>  pt, Segment s){
    ld t=prod_Scalaire(mk(s.b.F-s.a.F,s.b.S-s.a.S),mk(pt.F-s.a.F,pt.S-s.a.S));
    if(distance_square(s.a,s.b)==0){
        return sqrt(distance_square(pt,s.a));
    }
    t/=sqrt(distance_square(s.a,s.b));
    if(distance_square(pt,s.a)-t*t<=0)return 0;
    return sqrt(distance_square(pt,s.a)-t*t);
}
ld get_angle(Segment A){
    pair<ld,ld> v=mk(A.b.F-A.a.F,A.b.S-A.a.S);
    ld tem=norm(v);
    if(tem==0)return 0;
    v=mk(v.F/tem,v.S/tem);
   if(v.F==0){
        if(v.S>0)return Pi/2;
        else return 3*Pi/2;
   }
   tem=v.S/v.F;
   tem=atan(tem);
   if(tem<0)tem+=2*Pi;
   if(v.F>0)return tem;
   tem+=Pi;
   if(tem>=2*Pi)tem-=2*Pi;
   return tem;
}
pair<ld,ld> get_line(Segment A){
    if(A.a.F==A.b.F)return mk(A.a.F,1e18);
    pair<ld,ld> Diff=mk(A.b.F-A.a.F,A.b.S-A.a.S);
    ld a=Diff.S/Diff.F;
    return mk(A.a.S-A.a.F*a,a);
}
pair<ld,ld> Seg_intersection(Segment A, Segment B){
    pair<ld,ld> t1=get_line(A),t2=get_line(B);
    if(t1.S==1e18){
        return Seg_intersection(B,A);
    }
    if(t2.S==1e18){
        return mk((t2.F-t1.F)/t1.S,t2.F);
    }
    if(t1.S==t2.S){
        return mk(-1e18,-1e18);
    }
    ld x=(t2.F-t1.F)/(t1.S-t2.S);
    ld y=t1.F+t1.S*x;
    return mk(x,y);
}
ld Angle_from_Circle(Circle C,pair<ld,ld> A,pair<ld,ld> A1,ld ang1){
    Segment B;
    B.a=C.O;
    B.b=A;
    ld ans=get_angle(B);
    ans+=Pi/2;
    B.b=A1;
    ld temp=get_angle(B);
    temp+=Pi/2;
    if(temp>=2*Pi)temp-=2*Pi;
    ans+=ang1-temp;
    if(ans>=2*Pi)ans-=2*Pi;
    return ans;
}
Circle Circle_from_Angle(ld angle,pair<ld,ld> A,pair<ld,ld> B){
    Segment A1,A2;
    angle+=Pi/2;
    if(angle>2*Pi)angle-=2*Pi;
    A1.b=mk(A.F+cos(angle),A.S+sin(angle));
    A1.a=A;
    A2.a=A;
    A2.b=B;
    ld vv=get_angle(A2);
    if(abs(angle-vv)<1e-8||abs(abs(angle-vv)-Pi)<1e-8){
        Circle C;
        C.r=sqrt(distance_square(A,B))/2;
        C.O=mk((A.F+B.F)/2,(A.S+B.S)/2);
        return C;
    }
    pair<ld,ld> G=get_verticle(A,B);
    A2.a=mk((A.F+B.F)/2,(A.S+B.S)/2);
    A2.b=mk(A2.a.F+G.F,A2.a.S+G.S);
    Circle C;
    C.O=Seg_intersection(A1,A2);
    C.r=sqrt(distance_square(A,C.O));
    return C;
}
ld Maximum_Unfitness(Segment C,vector<pair<ld,ld> > P){
    ld val=0;
    for(auto i:P){
        ld t=get_Distance(i,C);
        val=max(abs(t),val);
    }
    return val;
}
ld Arc_unfitness(Circle C,ld angle1,ld angle2,vector<pair<ld,ld> > P){
    ld ans=0;
    ll n=P.size();
    for(int k=0;k<2*n-1;k++){
        int i=k/2;
        pair<ld,ld> temp=P[i];
        if(k%2){
            temp.F=(temp.F+P[i+1].F)/2;
            temp.S=(temp.S+P[i+1].S)/2;
        }
        ld ang=Angle_from_Circle(C,temp,P[0],angle1);
        bool inclu=true;
        if(angle1<=angle2){
            if(ang<angle1||ang>angle2)inclu=false;
        }else{
            if(ang<angle1&&ang>angle2)inclu=false;
        }
        if(inclu){
            ld t=sqrt(distance_square(C.O,P[i]))-C.r;
            t*=t;
            ans+=t;
        }else{
            ld t=min(distance_square(C.O,P[0]),distance_square(C.O,P.back()));
            t*=t;
            ans+=t;
        }
    }
    return ans;
}
ld Max_Arc_unfitness(Circle C,ld angle1,ld angle2,vector<pair<ld,ld> > P){
    ld ans=0;
    ll n=P.size();
    for(int k=0;k<2*n-1;k++){
        int i=k/2;
        pair<ld,ld> temp=P[i];
        if(k%2){
            temp.F=(temp.F+P[i+1].F)/2;
            temp.S=(temp.S+P[i+1].S)/2;
        }
        ld ang=Angle_from_Circle(C,temp,P[0],angle1);
        bool inclu=true;
        if(angle1<=angle2){
            if(ang<angle1||ang>angle2)inclu=false;
        }else{
            if(ang<angle1&&ang>angle2)inclu=false;
        }
        if(inclu){
            ld t=sqrt(distance_square(C.O,P[i]))-C.r;
            t=abs(t);
            ans=max(ans,t);
        }else{
            ld t=min(distance_square(C.O,P[0]),distance_square(C.O,P.back()));
            ans=max(ans,t);
        }
    }
    return ans;
}

ld Segment_unfitness(Segment C,vector<pair<ld,ld> > P){
    ld val=0;
    if(P.size()==0)return 0;
    for(auto i:P){
        ld t=get_Distance(i,C);
        t*=t;
        val+=t;
    }
    return val/(P.size());
}
