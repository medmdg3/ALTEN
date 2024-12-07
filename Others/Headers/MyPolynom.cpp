#include"MyPolynom.hpp"
using namespace std;
#define pb(a) push_back(a)
#define mk(a,b) make_pair(a,b)
#define F first
#define S second
#define V vector
#define sz() size()
typedef long long ll;
typedef long double ld;
        ll Polynomial::get_degree(){
            return coef.size()-1;;
        }
        ld Polynomial::get_coef(ll ind){
            if(ind>=coef.size())return 0;
            assert(ind>=0);
            return coef[ind];
        }
        void Polynomial::set_coef(ll ind,ld val){
            assert(ind>=0&&ind<coef.size());
            coef[ind]=val;
            while(coef.back()==0){
                coef.pop_back();
                if(coef.size()==0)break;
            }
        }
        void Polynomial::add_coef(ld val){
            if(val==0)return;
            coef.pb(val);
        }
        ll Polynomial::del_coef(){
            if(coef.size()==0)return -1;
            coef.pop_back();
            while(coef.back()==0){
                coef.pop_back();
                if(coef.size()==0)break;
            }
            return 0;
        }
        void Polynomial::set_Polynomial(vector<ld> new_Polynomial){
            if(new_Polynomial.size()==0){
                coef.clear();
                return;
            }
            while(new_Polynomial.back()==0){
                new_Polynomial.pop_back();
                if(new_Polynomial.size()==0)break;
            }
            coef=new_Polynomial;
        }
        vector<ld> Polynomial::get_Polynomial(){
            return coef;
        }
ld Polynomial_value(Polynomial A,ld val){
    ld ans=0,temp=1;
    for(int i=0;i<=A.get_degree();i++){
        ans+=A.get_coef(i)*temp;
        temp*=val;
    }
    return ans;
}
Polynomial Polynomial_Derive(Polynomial A){
    if(A.get_degree()==-1)return A;
    ll n=A.get_degree();
    vector<ld> ans;
    for(int i=1;i<=n;i++){
        ans.pb(i*A.get_coef(i));
    }
    A.set_Polynomial(ans);
    return A;
}
Polynomial Polynomial_Sum(Polynomial A,Polynomial B){
    ll n=max(A.get_degree(),B.get_degree());
    vector<ld> ans;
    for(int i=0;i<=n;i++){
        ans.pb(A.get_coef(i)+B.get_coef(i));
    }
    A.set_Polynomial(ans);
    return A;
}
Polynomial Polynomial_Shift(Polynomial A,ll n,ld val){
    vector<ld> ans,b=A.get_Polynomial();
    while(n>0){
        ans.pb(val);
        n--;
    }
    n*=-1;
    for(int i=n;i<b.size();i++)ans.pb(b[i]);
    A.set_Polynomial(ans);
    return A;
}
Polynomial Polynomial_Scale(Polynomial A,ld scale){
    for(int i=0;i<=A.get_degree();i++){
        A.set_coef(i,A.get_coef(i)*scale);
    }
    return A;
}
Polynomial Polynomial_Product(Polynomial A,Polynomial B){
    Polynomial C;
    for(int i=0;i<=A.get_degree();i++){
        Polynomial D=Polynomial_Scale(B,A.get_coef(i));
        D=Polynomial_Shift(D,i);
        C=Polynomial_Sum(C,D);
    }
    return C;
}
Polynomial Polynomials_Product(vector<Polynomial> A){
    assert(A.size());
    while(A.size()>1){
        ll n=A.size();
        A[n-2]=Polynomial_Product(A[n-2],A.back());
        A.pop_back();
    }
    return A[0];
}
Polynomial Polynomial_from_roots(vector<ld> roots){
    vector<Polynomial> A(roots.size()+1);
    A.back().set_Polynomial({1});
    for(int i=0;i<roots.size();i++){
        A[i].set_Polynomial({-roots[i],1});
    }
    return Polynomials_Product(A);
}
Polynomial Polynomial_integral(Polynomial A,ld val_0){
    vector<ld> a;
    a.pb(val_0);
    for(int i=0;i<=A.get_degree();i++){
        a.pb(A.get_coef(i)/(i+1));
    }
    A.set_Polynomial(a);
    return A;
}
Polynomial Polynomial_Approximal(vector<pair<ld,ld> > points){
    if(points.size()==0){
        Polynomial A;
        return A;
    }
    sort(points.begin(),points.end());
    vector<pair<ld,ld> > np;
    np.pb(points[0]);
    for(int i=1;i<points.size();i++){
        if(points[i].F==points[i-1].F){
            if(points[i].S==points[i-1].S)continue;
            assert(points[i].S!=points[i-1].S);
        }
        else np.pb(points[i]);
    }
    points=np;
    ll n=points.size();
    Matrix A;
    vector<vector<ld> > mat(n);
    for(int i=0;i<n;i++){
        ld po=1;
        for(int j=0;j<n;j++){
            mat[i].pb(po);
            po*=points[i].F;
        }
        mat[i].pb(points[i].S);
    }
    A.set_Matrix(mat);
   // Print_Matrix(A);
    A=Gauss_Elimination(A);
    vector<ld> ans;
    for(int i=0;i<n;i++)ans.pb(A.get_line(i).back());
    Polynomial C;
    C.set_Polynomial(ans);
    return C;
}