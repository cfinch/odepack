#include <iostream>
#include "odepack.hpp"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <boost/numeric/bindings/traits/traits.hpp>
#include <boost/numeric/bindings/traits/type_traits.hpp>
#include <boost/numeric/bindings/traits/detail/array.hpp>
#include <boost/numeric/bindings/traits/matrix_traits.hpp>

/* The C-style interface below still uses the Boost bindings, but uses
 * straight C arrays instead of Boost vectors.  I commented out the code
 * here and the C-array interface in the file odepack.hpp because I don't
 * see a need for this version.  Feel free to fix it if you do.
 */


//void f (int* neq, double* t, double* y, double* ydot) {
//    /* Parameters:
//     * neq: number of first-order ODE's
//     * t: value of independent variable
//     * y: values of y(t)
//     * ydot: vector of values of the derivative
//     */

//    // Compute ydot
//    ydot[0] = -0.04*y[0] + 1e4*y[1]*y[2];
//    ydot[2] = 3e7*y[1]*y[1];
//    ydot[1] = -ydot[0] - ydot[2];
//}


//void j (int* neq, double* t, double* y, int* ml, int* mu, double* pd, int* nrowpd) {
//    // dummy function that would compute the Jacobian if we wanted to do that
//}

//void c_style() {
//    // Do it old-school C style

//    int iopt, iout, istate, itask, itol, mf, neq;
//    double rtol, t, tout;

//    neq = 3;
//    double y[] = {1.0, 0.0, 0.0};

//    t = 0.0;
//    tout = 0.4;
//    itol = 2;
//    rtol = 1.0e-4;

//    double atol[] = {1e-6, 1e-10, 1e-6};

//    itask = 1;
//    istate = 1;
//    iopt = 0;
//    mf = 22;

//    std::cout << "---------- C Version -----------" << std::endl;
//    for (iout=1; iout<3; iout++) {
//        boost::numeric::bindings::odepack::lsode(f, &neq, y, &t, &tout, &itol, &rtol, atol, &itask,
//            &istate, &iopt, j, &mf);

//        std::cout << "At t= " << t << "   y[0]=" << y[0] << " y[1]=" << y[1] << " y[2]=" << y[2] << std::endl;

//        tout = tout*10;
//    }
//}

//-----------------------------------------------------------------------------

// Boost C++ version
void f (const int neq, const double t, const boost::numeric::ublas::vector<double> & y, 
        boost::numeric::ublas::vector<double> & ydot) {
    /* Compute right-hand-side vector ydot
     *
     * Parameters:
     * neq: number of first-order ODE's
     * t: value of independent variable
     * y: values of y(t)
     * ydot: vector of values of the derivative (the right-hand side)
     */
    
    ydot[0] = -0.04*y[0] + 1e4*y[1]*y[2];
    ydot[2] = 3e7*y[1]*y[1];
    ydot[1] = -ydot[0] - ydot[2];

}

// Boost C++ version
void j (const int neq, const double t, const boost::numeric::ublas::vector<double> & y, const int ml, const int mu, 
    boost::numeric::ublas::matrix<double>  & p, const int nrowpd) {
    /* Compute Jacobian
     *
     * Parameters:
     * neq: number of first-order ODE's
     * t: value of independent variable
     * y: values of y(t)
     * ml: value of lower part of the band for banded Jacobian
     * mu: value of upper part of the band for banded Jacobian
     * p: Jacobian matrix
     * nrowpd: dimension of Jacobian
     */

    p(0,0) = -0.04;
    p(0,1) = 1.0e4*y[2];
    p(0,2) = 1.0e4*y[1];
    p(1,0) = 0.04;
    p(1,2) = -p(0,2);
    p(2,1) = 6.0e7*y[1];
    p(1,1) = -p(0,1)-p(2,1);

}

void boost_style() {
    // do it Boost style
    using namespace boost::numeric::ublas;

    vector<double> y, atol;

    y.resize(3, false);
    atol.resize(3, false);

    y[0] = 1.0;
    y[1] = 0.0;
    y[2] = 0.0;

    atol[0] = 1e-6;
    atol[1] = 1e-10;
    atol[2] = 1e-6;

    int iopt, iout, istate, itask, itol, mf, neq;
    double rtol, t, tout;

    neq = 3;
    t = 0.0;
    tout = 0.4;
    itol = 2;
    rtol = 1.0e-4;
    itask = 1;
    istate = 1;
    iopt = 0;
    mf = 22;

    std::cout << "---------- Boost C++ Version -----------" << std::endl;
    for (iout=1; iout<3; iout++) {
        boost::numeric::bindings::odepack::lsode(f, neq, y, t, tout, 
            itol, rtol, atol, itask, istate, iopt, j, mf);

        std::cout << "At t= " << t << "   y[0]=" << y[0] << " y[1]=" << y[1] << " y[2]=" << y[2] << std::endl;

        tout = tout*10;
    }
    

}

int main()
{
//    c_style();
    boost_style();
}

