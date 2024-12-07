#include "Best_Circle.hpp"
using namespace std;
#define pb(a) push_back(a)
#define mk(a,b) make_pair(a,b)
#define F first
#define S second
#define V vector
#define sz() size()
typedef long long ll;
typedef long double ld;

ld distance_square(pair<ld,ld> P1,pair<ld,ld> P2){
    return (P1.F-P2.F)*(P1.F-P2.F)+(P1.S-P2.S)*(P1.S-P2.S);
}

ld Maximum_Unfitness(Circle C,vector<pair<ld,ld> > P){
    ld val=0;
    for(auto i:P){
        ld t=sqrt(distance_square(C.O,i))-C.r;
        val=max(abs(t),val);
    }
    return val;
}

ld Circle_unfitness(Circle C,vector<pair<ld,ld> > P){
    ld val=0;
    if(P.size()==0)return 0;
    for(auto i:P){
        ld t=sqrt(distance_square(C.O,i))-C.r;
        t*=t;
        val+=t;
    }
    return val/(P.size());
}
ld norm(pair<ld,ld> vect){
    return sqrt(vect.F*vect.F+vect.S*vect.S);
}

pair<ld,ld> get_verticle(pair<ld,ld> P1,pair<ld,ld> P2){
    ld X=P2.F-P1.F,Y=P2.S-P1.S;
    if(Y==0){
        return mk(0,1);
    }
    ld x1=1,y1=-X/Y;
    ld temp=norm(mk(x1,y1));
    x1/=temp;
    y1/=temp;
    return mk(x1,y1);
}

pair<ld,ld> best_center(pair<ld,ld> P1,pair<ld,ld> P2,ld r,bool Down){
    ld t=sqrt(distance_square(P1,P2))/2;
    if(t>r){
        assert(1==0);
    }
    pair<ld,ld> vert=get_verticle(P1,P2);
    ld t1=sqrt(r*r-t*t);
    if(Down)t1*=-1;
    return mk((P1.F+P2.F)/2+vert.F*t1,(P1.S+P2.S)/2+vert.S*t1);
}