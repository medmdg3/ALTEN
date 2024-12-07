#include"Headers/My_Headers.hpp"
using namespace std;
#define pb(a) push_back(a)
#define mk(a,b) make_pair(a,b)
#define F first
#define S second
#define V vector
#define sz() size()
typedef long long ll;
typedef long double ld;
const ld Max_Deviation=0.5;
const ll angles_decomposition=20;
/// @brief Customisable. \n Calculate the cost of a transiction from a shape to another one
/// @tparam T1 the type of input
/// @param vals a vector contaning the needed input parameter
/// @return the value described above
template<typename T1>
ld Insmouthness_Cost(vector<T1> vals){
    return 1000*vals[0]*vals[0];
}
/// @brief Customisable. \n Calculate the cost of moving along a given shape (here is an arc as example)
/// @param C the circle where the arc belong
/// @param angle1 describes the start of the arc
/// @param angle2 describes the end of the arc
/// @return the value described above
ld Cost_of_Arc(Circle C,ld angle1,ld angle2){
    if(angle2<angle1)angle2+=2*Pi;
    angle2-=angle1;
    angle2/=2*Pi;
    return 10*angle2/C.r;
}
/// @brief Finds a set of Arcs that fits a set of points the best
/// @param P The given set of points
/// @param Max_tolerance The max accepted value of a unfitness in any given point
/// @param init_angle the starting angle of the first arc
/// @return the value described above, the arcs are described as pair the first element contains the coordinates of the starting point and the angle at this point, the second element is the circle described by the arc. Note that the end of an arc is the beggining of the next one.
vector<pair<pair<pair<ld,ld>,ld>,Circle> > Solve(vector<pair<ld,ld> > P,ld Max_tolerance=1,ld init_angle=0){
    ld dO=2*Pi/angles_decomposition;
    cout<<1<<endl;
    ll n=P.size();
    ld dp[n][angles_decomposition];

    pair<pair<ll,ll> ,Circle> Next[n][angles_decomposition];
    Circle Cir;
    Cir.r=1;
    Cir.O.F=-1;
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<angles_decomposition;j++){
            dp[i][j]=1e18*ll(i!=n-1);
            Next[i][j]=mk(mk(-1,-1),Cir);
        }
    }
    for(int i=n-1;i>=0;i--){
       vector<pair<ld,ld> > Temp={P[i]};
       cout<<i<<endl;
       for(int j=i+1;j<n;j++){
        Temp.pb(P[j]);
        /*Circle C=Best_Circle(Temp,Circle_unfitness);
        //Segment Seg;
        ld vv=Circle_unfitness(C,Temp);
        Seg.a=Temp[0],Seg.b=Temp.back();
        ld ang=get_angle(Seg);
        ll t=ang/dO;
        ld to=Segment_unfitness(Seg,Temp)*Temp.size();*/
        for(int T=0;T<angles_decomposition;T++){
            Circle C=Circle_from_Angle(T*dO,P[i],P[j]);
            ld ang1=Angle_from_Circle(C,P[j],P[i],T*dO);
            ld unfit=Arc_unfitness(C,T*dO,ang1,Temp);
            ld Val=Max_Arc_unfitness(C,T*dO,ang1,Temp);
            if(Val>Max_tolerance)
                continue;
            ld to=unfit+Cost_of_Arc(C,T*dO,ang1);
            ll te=ang1/dO;
            for(int k=0;k<angles_decomposition;k++){
             vector<ld> temp1={dO*ld((k-te+angles_decomposition)%angles_decomposition)};
             ld t1=dp[j][k]+to+Insmouthness_Cost(temp1);
             if(t1<dp[i][T]){
                dp[i][T]=t1;
                Next[i][T]=mk(mk(j,k),C);
             }
            }
        }
       }
    }
    pair<ll,ll> c=mk(0,(ll (init_angle/dO)+angles_decomposition)%angles_decomposition);
    ld cost=0;
    
    vector<pair<pair<pair<ld,ld>,ld>,Circle> > Ans;
    while(c.F!=-1){
        //cout<<P[c.F].F<<" "<<P[c.F].S<<" "<<c.S*dO*180/Pi<<" ";
        pair<pair<ll,ll> ,Circle> temp=Next[c.F][c.S];
        cost+=dp[c.F][c.S];
        Ans.pb(mk(mk(P[c.F],c.S*dO*180/Pi),temp.S));
        c=temp.F;
        if(c.F==-1)break;
    }
   // cout<<cost<<endl;
    return Ans;
}

int main(){
    //vector<pair<ld,ld> > P={mk(0.447985,1.91722),mk(-0.932662,3.97938),mk(-1.77442,6.31392),mk(-2.03,9.95923),mk(-2.03,9.95923),mk(-2.03077,11.9592),mk(-2.03154,13.9592),mk(-2.03231,15.9592),mk(-2.03308,17.9592),mk(-2.03385,19.9592)};
   vector<pair<ld,ld> > P;
    freopen("out.txt","r",stdin);
    freopen("out2.txt","w",stdout);
    ll n;
    cin>>n;
    for(int i=0;i<n;i++){
        ld x,y,z;
        cin>>x>>y>>z;
        P.pb(mk(x,y));
    //    cout<<"mk("<<x<<","<<y<<"),";
    }
    vector<pair<pair<pair<ld,ld>,ld>,Circle> > Ans=Solve(P,4,Pi/2);
    for(auto i:Ans){
        cout<<i.F.F.F<<" "<<i.F.F.S<<" "<<i.F.S<<" "<<i.S.O.F<<" "<<i.S.O.S<<" "<<i.S.r<<endl;
    }
}
