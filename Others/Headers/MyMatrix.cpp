#include"MyMatrix.hpp"
using namespace std;
#define pb(a) push_back(a)
#define mk(a,b) make_pair(a,b)
#define F first
#define S second
#define V vector
#define sz() size()
typedef long long ll;
typedef long double ld;
    ll Matrix::get_nbr_lines() {
        return nbr_lines;
    }
    ll Matrix::get_nbr_columns() {
        return nbr_columns;
    }
    void Matrix::init(ll n, ll p) {
        if (p == -1) p = n;
        assert(p >= 0 && n >= 0);
        nbr_lines = n;
        nbr_columns = p;
        Values.clear();
        Values.resize(n);
        for (int i = 0; i < n; i++) {
            Values[i].resize(p);
        }
    }
    vector<ld> Matrix::get_line(ll ind) {
        assert(ind >= 0 && ind < nbr_lines);
        return Values[ind];
    }

    vector<ld> Matrix::get_column(ll ind) {
        assert(ind >= 0 && ind < nbr_columns);
        vector<ld> ans;
        for (int i = 0; i < nbr_lines; i++) ans.pb(Values[i][ind]);
        return ans;
    }
    ld Matrix::get_value(ll i, ll j) {
        assert(i >= 0 && j >= 0 && i < nbr_lines && j < nbr_columns);
        return Values[i][j];
    }
    vector<vector<ld> > Matrix::get_Matrix() {
        return Values;
    }
    void Matrix::set_line(ll ind, vector<ld> new_line) {
        assert(ind >= 0 && ind < nbr_lines && new_line.size() == nbr_columns);
        Values[ind] = new_line;
        return;
    }
    void Matrix::set_column(ll ind, vector<ld> new_column) {
        assert(ind >= 0 && ind < nbr_columns && new_column.size() == nbr_lines);
        for (int i = 0; i < nbr_lines; i++) Values[i][ind] = new_column[i];
        return;
    }
    void Matrix::set_value(ll i, ll j, ld new_value) {
        assert(i >= 0 && j >= 0 && i < nbr_lines && j < nbr_columns);
        Values[i][j] = new_value;
    }
    void Matrix::set_Matrix(vector<vector<ld> > new_matrix) {
        nbr_lines = new_matrix.size();
        if (nbr_lines == 0) nbr_columns = 0;
        else nbr_columns = new_matrix[0].size();
        for (int i = 0; i < nbr_lines; i++) assert(new_matrix[i].size() == nbr_columns);
        Values = new_matrix;
    }
ld Matrix_distance(Matrix A, Matrix B) {
    assert(A.get_nbr_lines() == B.get_nbr_lines() && A.get_nbr_columns() == B.get_nbr_columns());
    ld sum = 0;
    for (int i = 0; i < A.get_nbr_lines(); i++)
        for (int j = 0; j < A.get_nbr_columns(); j++) {
            ld temp = (A.get_value(i, j) - B.get_value(i, j));
            sum += temp * temp;
        }
    return sqrt(sum);
}
void Print_Matrix(Matrix A) {
    cout << A.get_nbr_lines() << endl;
    cout << "{";
    for (int i = 0; i < A.get_nbr_lines(); i++) {
        cout << "{";
        for (int j = 0; j < A.get_nbr_columns(); j++) {
            cout << A.get_value(i, j);
            if (j != A.get_nbr_columns() - 1) cout << "; ";
        }
        cout << "} \n";
    }
    cout << "}";
    cout << endl;
}
Matrix Scale_Matrix(ll n, ld val) {
    assert(n >= 0);
    Matrix ans;
    ans.init(n, n);
    for (int i = 0; i < n; i++) ans.set_value(i, i, val);
    return ans;
}
Matrix Matrix_Fill(ll n, ll p , ld val ) {
    if (p == -1) p = n;
    assert(n >= 0 && p >= 0);
    Matrix ans;
    vector<vector<ld> > a(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            a[i].pb(val);
        }
    }
    ans.set_Matrix(a);
    return ans;
}
Matrix Matrix_Null(ll n, ll p ) {
    if (p == -1) p = n;
    assert(n >= 0 && p >= 0);
    return Matrix_Fill(n, p, 0);
}
Matrix Matrix_identity(ll n) {
    assert(n >= 0);
    return Scale_Matrix(n, 1);
}
Matrix Matrix_Sum(Matrix A, Matrix B) {
    assert(A.get_nbr_lines() == B.get_nbr_lines() && A.get_nbr_columns() == B.get_nbr_columns());
    ll n = A.get_nbr_lines(), p = A.get_nbr_columns();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++) A.set_value(i, j, A.get_value(i, j) + B.get_value(i, j));
    return A;
}
Matrix Matrix_Product(Matrix A, Matrix B) {
    assert(B.get_nbr_lines() == A.get_nbr_columns());
    ll n = A.get_nbr_lines(), p = B.get_nbr_columns(), temp = A.get_nbr_columns();
    Matrix ans;
    ans.init(n, p);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++) {
            ld sum = 0;
            for (int k = 0; k < temp; k++) {
                sum += A.get_value(i, k) * B.get_value(k, j);
            }
            ans.set_value(i, j, sum);
        }
    return ans;
}
void Matrix_Scale_Line(Matrix &A, ll ind, ld coef) {
    assert(ind >= 0 && ind < A.get_nbr_lines());
    for (int i = 0; i < A.get_nbr_columns(); i++) {
        A.set_value(ind, i, A.get_value(ind, i) * coef);
    }
    return;
}
Matrix Matrix_Scale(Matrix A, ld coef) {
    ll n = A.get_nbr_lines(), p = A.get_nbr_columns();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            A.set_value(i, j, A.get_value(i, j) * coef);
        }
    }
    return A;
}
Matrix Matrix_Inverse(Matrix A) {
    ll n = A.get_nbr_lines(), p = A.get_nbr_columns();
    assert(n == p);
    Matrix Ans, B = A;
    Ans = Matrix_identity(n);
    for (int j = 0; j < n; j++) {
        ll ind = -1;
        for (int i = j; i < n; i++) {
            if (B.get_value(i, j) != 0) {
                ind = j;
                if (i == j) break;
                vector<ld> new_line1 = B.get_line(j), new_line2 = Ans.get_line(j);
                for (int k = 0; k < n; k++) {
                    new_line1[k] += B.get_value(i, k);
                    new_line2[k] += Ans.get_value(i, k);
                }
                B.set_line(j, new_line1);
                Ans.set_line(j, new_line2);
                break;
            }
        }
        assert(ind != -1);
        ld temp = 1;
        temp /= B.get_value(ind, j);
        Matrix_Scale_Line(B, ind, temp);
        Matrix_Scale_Line(Ans, ind, temp);
        for (int i = 0; i < n; i++) {
            if (i == ind) continue;
            temp = B.get_value(i, j);
            vector<ld> new_line1 = B.get_line(i), new_line2 = Ans.get_line(i);
            for (int k = 0; k < n; k++) {
                new_line1[k] -= temp * B.get_value(ind, k);
                new_line2[k] -= temp * Ans.get_value(ind, k);
            }
            B.set_line(i, new_line1);
            Ans.set_line(i, new_line2);
        }
    }
    return Ans;
}
Matrix Matrix_Transpose(Matrix A) {
    Matrix Ans;
    Ans.init(A.get_nbr_columns(), A.get_nbr_lines());
    for (int i = 0; i < A.get_nbr_columns(); i++) {
        Ans.set_line(i, A.get_column(i));
    }
    return Ans;
}
Matrix Gauss_Elimination(Matrix A){
    ll n=A.get_nbr_lines();
    for(int j=0;j<n;j++){
        ll ind=j;
        if(A.get_value(j,j)==0)
        for(int i=0;i<n;i++){
            if(A.get_value(i,i))continue;
            if(A.get_value(i,j)>1e-10){
                if(i==j)break;
                vector<ld> new_line=A.get_line(j);
                for(int k=0;k<new_line.size();k++){
                    new_line[k]+=A.get_value(i,k);
                }
                A.set_line(j,new_line);
                break;
            }
            if(i==n-1)ind=-1;
        }
        if(ind==-1)continue;
        Matrix_Scale_Line(A,j,(1/A.get_value(j,j)));
        for(int i=0;i<n;i++){
            if(i==j)continue;
            ld temp=A.get_value(i,j);
            if(temp==0)continue;
            vector<ld> new_line=A.get_line(i);
            for(int k=j;k<A.get_nbr_columns();k++){
                new_line[k]-=temp*A.get_value(j,k);
            }
            A.set_line(i,new_line);
        }
    }
    return A;
}
