#include<bits/stdc++.h>
#include"MyMatrix.hpp"
#include"MyMatrix.cpp"
using namespace std;
#define pb(a) push_back(a)
#define mk(a,b) make_pair(a,b)
#define F first
#define S second
#define V vector
#define sz() size()
typedef long long ll;
typedef long double ld;

/**
 * @brief This function solves the finite horizon Discrete Linear Quadratic Regulator (DLQR) problem.
 * The underlying equation is \f$ x_{t+1} = Ax_t + Bu_t \f$.
 * The goal is to find values of \f$ u \f$ that minimize
 * \f$ \sum_{t=0}^{N-1} (x_t^T Q x_t + u_t^T R u_t) + x_N^T Q_f x_N \f$,
 * where \f$ Q = Q^T \geqslant 0 \f$, \f$ Q_f \geqslant 0 \f$, \f$ R = R^T > 0 \f$,
 * and \f$ A \f$, \f$ B \f$, \f$ Q \f$, \f$ R \f$, \f$ Q_f \f$, \f$ x_0 \f$, and \f$ N \f$ are fixed. \n
 * The main source of the algorithm idea: https://stanford.edu/class/ee363/lectures/dlqr.pdf.
 *
 * @attention The algorithm has been optimized.
 *
 * @param A As described above.
 * @param B As described above.
 * @param Q As described above.
 * @param Qf As described above.
 * @param R As described above.
 * @param X_init As described above.
 * @param N As described above.
 * @return A pair of vectors containing the sequences \f$ (x_t)_{0 \leqslant t \leqslant N} \f$
 *         and \f$ (u_t)_{0 \leqslant t < N} \f$.
 */
pair<vector<Matrix>,vector<Matrix> > DLQR(Matrix A,Matrix B,Matrix Q,Matrix Qf,Matrix R,Matrix X_init,ll N){
    vector<Matrix> P(N+1);
    P[N]=Qf;
    for(int i=N-1;i>0;i--){
        Matrix A1=Matrix_Product(Matrix_Product(Matrix_Transpose(A),P[i+1]),A);// A'PA
        Matrix A2=Matrix_Product(Matrix_Product(Matrix_Transpose(B),P[i+1]),A);//B'PA
        Matrix A3=Matrix_Product(Matrix_Product(Matrix_Transpose(A),P[i+1]),B);//A'PB
        A3=Matrix_Scale(A3,-1);
        Matrix A4=Matrix_Product(Matrix_Product(Matrix_Transpose(B),P[i+1]),B);//B'PB
        Matrix A5=Matrix_Inverse(Matrix_Sum(R,A4));//(R+B'PB)`
        P[i]=Matrix_Sum(Q,Matrix_Sum(A1,Matrix_Product(Matrix_Product(A3,A5),A2)));
        if(Matrix_distance(P[i],P[i+1])<max(Matrix_distance(Qf,Matrix_Null(P[i].get_nbr_lines())),(ld) (1)/1e6)/1e9){
            while(i--){
                P[i]=P[i+1];
            }
        }
    }
    vector<Matrix> X,U;
    X.pb(X_init);
    for(int i=0;i<N;i++){
        Matrix A2=Matrix_Product(Matrix_Product(Matrix_Transpose(B),P[i+1]),A);//B'PA
        Matrix A4=Matrix_Product(Matrix_Product(Matrix_Transpose(B),P[i+1]),B);//B'PB
        Matrix A5=Matrix_Inverse(Matrix_Sum(R,A4));//(R+B'PB)`
        Matrix K=Matrix_Scale(Matrix_Product(A5,A2),-1);
        U.pb(Matrix_Product(K,X[i]));
        X.pb(Matrix_Sum(Matrix_Product(A,X[i]),Matrix_Product(B,U[i])));
    }
    return mk(X,U);
}
int main(){
    Matrix A,B,Q,R,Qf,X_init;
    ll N=20000;
    A.set_Matrix({{1,0.001,0,0},{0,0.9999,0.003,0},{0,0,1,0.001},{0,-0.0005,0.03,1}});
    B.set_Matrix({{0},{0.002},{0},{0.005}});
    Q.set_Matrix({{1,0,0,0},{0,0,0,0},{0,0,1,0},{0,0,0,0}});
    Qf.set_Matrix({{1000,0},{0,1000000}});
    R=Scale_Matrix(1,1);
    X_init.set_Matrix({{0},{0},{55},{0}});
    pair<vector<Matrix>,vector<Matrix> > Ans=DLQR(A,B,Q,Q,R,X_init,N);
    vector<ld> O;
    for(int i=0;i<=N;i++){
        O.pb(Ans.F[i].get_value(2,0));
    }
    cout<<"[";
    for(int i=0;i<=N;i+=200){
        cout<<O[i]<<", ";
    }
    cout<<"]";
}
