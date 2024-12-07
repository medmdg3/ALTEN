#pragma once
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
/// @brief Helps manipulate Polynomials; it uses a vector of long double to represent each of them.
class Polynomial {
    private:
        vector<ld> coef;
    public:
        /// @brief Allows reading the degree of a Polynomial.
        /// @return The degree of the Polynomial.
        ll get_degree();

        /// @brief Allows reading a coefficient in the Polynomial.
        /// @param ind The index of the coefficient \f$a_i\f$ corresponding to \f$X^i\f$.
        /// @return The coefficient \f$a_{ind}\f$.
        ld get_coef(ll ind);

        /// @brief Allows changing the value of a coefficient.
        /// @param ind The index of the coefficient to change.
        /// @param val The new value.
        void set_coef(ll ind, ld val);

        /// @brief Allows extending the Polynomial by one index.
        /// @param val The value of the coefficient to be added.
        void add_coef(ld val);

        /// @brief Allows removing the last coefficient of a Polynomial.
        /// @return -1 if the Polynomial is null; otherwise, it returns 0.
        ll del_coef();

        /// @brief Allows replacing the existing Polynomial.
        /// @param new_Polynomial A vector containing the coefficients of the new Polynomial,
        ///                       where \f$new_Polynomial[i]\f$ corresponds to \f$X^i\f$.
        void set_Polynomial(vector<ld> new_Polynomial);

        /// @brief Allows reading all the coefficients of a Polynomial.
        /// @return A vector containing all the coefficients, where the value at index \f$[i]\f$ corresponds to \f$X^i\f$.
        vector<ld> get_Polynomial();
};
/// @brief Computes the value of a Polynomial at a given point.
/// @param A The corresponding polynomial.
/// @param val The given point.
/// @return The corresponding value \f$A(val)\f$.
ld Polynomial_value(Polynomial A,ld val);
/// @brief Construct  the derivative of a polynomial
/// @param A The polynomial
/// @return The derivative
Polynomial Polynomial_Derive(Polynomial A);
/// @brief Construct a polynomial who is equal to the sum of two other given polynomials
/// @param A The first given polynomial
/// @param B The second given polynomial
/// @return The sum of the two given polynomials 
Polynomial Polynomial_Sum(Polynomial A,Polynomial B);
/// @brief Construct a polynomial shifted to the right or to the left by a certain value \f$|n|\f$, \n it erases the first \f$|n|\f$ elements if it is being shifted to the right, or multiplying the polynom by \f$X^{|n|}\f$ if the shift is to the left, while filling the new coeficiant with a given value
/// @param A The polynom containing the original values
/// @param n Defines how the polynomial will be shifted: \n    It will be shifted to the left by \f$|n|\f$ if \f$n>=0\f$ \n It will be shifted to the right by \f$|n|\f$ if \f$n<0\f$
/// @param val The given value
/// @return The constructed polynomial
Polynomial Polynomial_Shift(Polynomial A,ll n,ld val=0);
/// @brief Construct polynomial sclaed with a given scale
/// @param A The polynomial cointaining the original values
/// @param scale The given sclae
/// @return The constructed polynomial
Polynomial Polynomial_Scale(Polynomial A,ld scale);
/// @brief Construct a polynomial who is equal to the product of two other given polynomials
/// @param A The first given polynomial
/// @param B The second given polynomial
/// @return The product of the two given polynomials 
Polynomial Polynomial_Product(Polynomial A,Polynomial B);
/// @brief Construct a polynomial who is equal to the product of a many polynomials
/// @param A A vector containing the polynomials to be multiplied
/// @return The product of the given polynomials 
Polynomial Polynomials_Product(vector<Polynomial> A);
/// @brief Construct a monic polynomial from it's roots
/// @param roots A vector containing all the roots, each one repeated according to it's degree
/// @return The corresponding polynomial
Polynomial Polynomial_from_roots(vector<ld> roots);
/// @brief Contruct an integral of a given polynomial
/// @param A the given polynomial
/// @param val_0 The coef corresponding to \f$X^0\f$ in the new polynomial 
/// @return The constructed polynomial
Polynomial Polynomial_integral(Polynomial A,ld val_0=0);
/// @brief Construct the polynomial of the smallest degree such that it passes through some given points (if it exists) 
/// @param points A vector of pairs, where each pair contains the coordinates of a given point
/// @return The constructed polynomial
Polynomial Polynomial_Approximal(vector<pair<ld,ld> > points);