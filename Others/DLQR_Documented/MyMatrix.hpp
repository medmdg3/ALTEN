#pragma once
#include<bits/stdc++.h>
using namespace std;
#define pb(a) push_back(a)
#define mk(a,b) make_pair(a,b)
#define F first
#define S second
#define V vector
#define sz() size()
typedef long long ll;
typedef long double ld;
/// @brief This class is used to represent a matrix using a vector of vectors of the same size.
class Matrix{
    private:
        ll nbr_lines = 0, nbr_columns = 0;
        vector<vector<ld> > Values;
    public:
    /// @brief Used to read the number of rows in the matrix.
    /// @return The number of rows in the matrix.
        ll get_nbr_lines();
    
    /// @brief Used to read the number of columns in the matrix.
    /// @return The number of columns in the matrix.
    ll get_nbr_columns() ;
    /// @brief Initializes the size of the matrix and fills it with zeros.
    /// @param n The new number of rows.
    /// @param p The new number of columns.
    void init(ll n, ll p);
    
    /// @brief Obtains a row of the matrix.
    /// @param ind The index of the row.
    /// @return A vector containing the elements of the row.
    vector<ld> get_line(ll ind);
        /// @brief Obtains a column of the matrix.
    /// @param ind The index of the column.
    /// @return A vector containing the elements of the column.
    vector<ld> get_column(ll ind);
        /// @brief Reads a value in the matrix.
    /// @param i The index of the row of the value.
    /// @param j The index of the column of the value.
    /// @return The value.
    ld get_value(ll i, ll j);
    
    /// @brief Reads all the values of the matrix.
    /// @return A vector containing all the rows of the matrix.
    vector<vector<ld> > get_Matrix();
        /// @brief Modifies the values of a row.
    /// @param ind The index of the row to be modified.
    /// @param new_line A vector containing the new values.
    void set_line(ll ind, vector<ld> new_line);
    
    /// @brief Modifies the values of a column.
    /// @param ind The index of the column to be modified.
    /// @param new_column A vector containing the new values.
    void set_column(ll ind, vector<ld> new_column) ;
    
    /// @brief Modifies a value in the matrix.
    /// @param i The index of the row of the value.
    /// @param j The index of the column of the value.
    /// @param new_value The new value.
    void set_value(ll i, ll j, ld new_value);
    /// @brief Allows modification of the entire matrix.
    /// @param new_matrix A vector containing the values of the new matrix.
    void set_Matrix(vector<vector<ld> > new_matrix);
};
/// @brief Calculates the distance between two matrices.
/// @param A The first matrix.
/// @param B The second matrix.
/// @return The Euclidean distance between the matrices.
ld Matrix_distance(Matrix A, Matrix B);
/// @brief Prints a matrix.
/// @param A The matrix to be printed.
void Print_Matrix(Matrix A);
/// @brief Constructs a scalar matrix.
/// @param n The size of the matrix.
/// @param val The scalar value.
/// @return The desired matrix \f$val \cdot I_n \f$.
Matrix Scale_Matrix(ll n, ld val);
/// @brief Constructs a matrix where all entries are filled with the same value.
/// @param n The number of rows of the matrix.
/// @param p The number of columns, default is the same as the number of rows.
/// @param val The value to fill all entries, default is 1.
/// @return The desired matrix.
Matrix Matrix_Fill(ll n, ll p = -1, ld val = 1);
/// @brief Constructs a zero matrix.
/// @param n The number of rows of the matrix.
/// @param p The number of columns, default is the same as the number of rows.
/// @return The desired matrix.
Matrix Matrix_Null(ll n, ll p = -1);
/// @brief Constructs the identity matrix \f$I\f$.
/// @param n The size of the matrix.
/// @return The desired identity matrix.
Matrix Matrix_identity(ll n);
/// @brief Adds two matrices.
/// @param A The first matrix to be added.
/// @param B The second matrix to be added.
/// @return The sum of the two matrices.
Matrix Matrix_Sum(Matrix A, Matrix B) ;
/// @brief Multiplies two matrices.
/// @param A The first matrix to be multiplied.
/// @param B The second matrix to be multiplied.
/// @return The matrix product of the two matrices.
Matrix Matrix_Product(Matrix A, Matrix B) ;
/// @brief Multiplies one row of the matrix by a given value.
/// @param A The matrix to be modified.
/// @param ind The index of the row to be modified.
/// @param coef The given value.
void Matrix_Scale_Line(Matrix &A, ll ind, ld coef);
/// @brief Constructs a matrix where all values are multiplied by a given value.
/// @param A The matrix containing the original values.
/// @param coef The given value.
/// @return The desired matrix.
Matrix Matrix_Scale(Matrix A, ld coef);
/// @brief Constructs the inverse of a matrix using Gauss Elimination.
/// Quadratic space complexity with respect to the number of lines in the matrix and cubic time complexity.
/// @param A The matrix to be inverted.
/// @return The inverse of the matrix.
Matrix Matrix_Inverse(Matrix A);
/// @brief Constructs the transpose of a matrix.
/// @param A The matrix containing the original values.
/// @return The transpose of matrix A.
Matrix Matrix_Transpose(Matrix A);