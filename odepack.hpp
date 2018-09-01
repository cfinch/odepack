#include <iostream>
/*
 * 
 * Copyright (c) Craig Finch 2007
 * Shamelessly stolen from lapack.hpp, which is
 * Copyright (c) Toon Knapen & Kresimir Fresl 2003
 *
 * Permission to copy, modify, use and distribute this software 
 * for any non-commercial or commercial purpose is granted provided 
 * that this license appear on all copies of the software source code.
 *
 * Authors assume no responsibility whatsoever for its use and makes 
 * no guarantees about its quality, correctness or reliability.
 *
 * KF acknowledges the support of the Faculty of Civil Engineering, 
 * University of Zagreb, Croatia.
 *
 * CF acknowledges the support of the University of Central Florida,
 * the Institute for Simulation and Training, the Nanoscience
 * Technology Center, and the I2 Lab.
 *
 */

#ifndef BOOST_NUMERIC_BINDINGS_ODEPACK_ODEPACK_HPP
#define BOOST_NUMERIC_BINDINGS_ODEPACK_ODEPACK_HPP

#include <boost/numeric/bindings/traits/traits.hpp>
#include "odepack.h"

#ifndef BOOST_NUMERIC_BINDINGS_NO_STRUCTURE_CHECK 
#  include <boost/static_assert.hpp>
#  include <boost/type_traits/is_same.hpp>
#endif 

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

namespace boost { namespace numeric { namespace bindings { 

  namespace odepack {

    namespace detail {

    // The double-precision version
      inline 
      void lsode (void (*pf)(int* neq, double* t, double* y, double* ydot),
          int const neq, double* y,
          double & t, double tout, int itol, double rtol,
          double * atol, int itask, int & istate,
          int iopt, double* rwork, int lrw, int* iwork,
          int liw, 
          void (*pjac)(int* neq, double* t, double* y, int* ml, int* mu, double* pd, int* nrowpd),
          int mf) 
      {
        ODEPACK_DLSODE (pf, &neq, y, &t, &tout, &itol, &rtol,
          atol, &itask, &istate, &iopt, rwork, &lrw, iwork,
          &liw, pjac, &mf);
      }
 
    // The single-precision version
      inline 
      void lsode (void (*pf)(int* neq, float* t, float* y, float* ydot),
          int const neq, float* y,
          float & t, float tout, int itol, float rtol,
          float * atol, int itask, int & istate,
          int iopt, float* rwork, int lrw, int* iwork,
          int liw, 
          void (*pjac)(int* neq, float* t, float* y, int* ml, int* mu, float* pd, int* nrowpd),
          int mf) 
      {
        ODEPACK_SLSODE (pf, &neq, y, &t, &tout, &itol, &rtol,
          atol, &itask, &istate, &iopt, rwork, &lrw, iwork,
          &liw, pjac, &mf);
      }

    // Utilities
      inline
      void dsrcom (double * rsav, int * isav, int job) {
        ODEPACK_DSRCOM (rsav, isav, &job);
      }

      inline
      void dintdy (double t, int k, double * rwork21, int nyh, double * dky, int & iflag) {
        ODEPACK_DINTDY (&t, &k, rwork21, &nyh, dky, &iflag);
      }

     } // namespace detail

//     // ---------- The C Version -----------
//     // for educational and debugging purposes
//    template <typename Any>     // where Any can be float or double
//    inline
//     int lsode (void (*pf)(int* neq, Any* t, Any* y, Any* ydot), 
//        int* neq, Any* y, Any* t, Any* tout, int* itol, Any* rtol,
//        Any* atol, int* itask, int* istate, int* iopt, 
//        void (*pj)(int* neq, Any* t, Any* y, int* ml, int* mu, Any* pd, int* nrowpd),
//        int* mf) {
//        /* Parameters:
//         * ydot:
//         * neq: number of first-order ODE's
//         * y: values of y(t) at t=t1
//         * t: initial value of independent variable
//         * tout: next value independent variable t
//         * itol: 1 indicates ATOL is scalar, 2 indicates ATOL is array
//         * rtol: relative tolerance
//         * atol: Absolute tolerance for each i in Y(i) (scalar or array)
//         * itask: 1 indicates that DLSODE is to compute output values of y
//         * istate: ISTATE=1 for first call, ISTATE=2 for subsequent calls
//         *      (Automatically updated to 2 if DLSODE was successful)
//         * iopt: =0 for no optional inputs, =1 for optional inputs
//         * mf: Method flag.  Possible values are:
//         */

//        // Local work variables
//        double rwork[58];
//        int iwork[23];

//        int lrw = 58;
//        int liw = 23;


//        // Aside from local variables, inputs are just passed through
//        detail::lsode(pf, neq, y, t, tout, itol, rtol, atol, itask, istate,
//            iopt, rwork, &lrw, iwork, &liw, pj, mf);

//        return(1);
//    } // lsode, C version


    static double * rwork;
    static int * iwork;
    static int lrw, liw;

    // ---------- The Boost C++ Version -----------
    // need to template this for float and double
     int lsode (void (*pf)(int* neq, double* t, double* y, double* ydot),
        int neq, boost::numeric::ublas::vector<double> & y, double & t, double tout, int itol, double rtol,
        boost::numeric::ublas::vector<double> & atol, int itask, int & istate, int iopt, 
        void (*pjac)(int* neq, double* t, double* y, int* ml, int* mu, double* pd, int* nrowpd),
        int mf) {
        /* Parameters:
         * neq: number of first-order ODE's
         * y: values of y(t) at t=t1
         * t: initial value of independent variable
         * tout: next value independent variable t
         * itol: 1 indicates ATOL is scalar, 2 indicates ATOL is array
         * rtol: relative tolerance
         * atol: Absolute tolerance for each i in Y(i) (scalar or array)
         * itask: 1 indicates that DLSODE is to compute output values of y
         * istate: ISTATE=1 for first call, ISTATE=2 for subsequent calls
         *      (Automatically updated to 2 if DLSODE was successful)
         * iopt: =0 for no optional inputs, =1 for optional inputs
         * mf: Method flag.  Possible values are:
         */

        // Local work variables

        int ml, mu;
        static int nextcall = 0;        
        static double * rsave;
        static int * isave;

        // On the first call...
        if (nextcall != 1) {
            // Compute length of work arrays
            ml = 5;   // totally made these value up
            mu = 5;

            switch (mf) {
                case 10 : lrw = 20 + 16*neq;
                          break;
                case 21 :
                case 22 : lrw = 22 + 9*neq + (int)pow(neq,2);
                          break;
                case 24 : 
                case 25 : lrw = 22 + 10*neq + (2*(ml) + (mu))*neq;
                          break;
            }

            switch (mf) {
                case 10 : liw = 20;
                          break;
                case 21 : 
                case 22 : 
                case 24 : 
                case 25 : liw = 20 + neq;
                          break;
            }

            // Allocate work arrays
            rwork = new double [lrw];       // these HAVE to be static!
            iwork = new int [liw];

           // Set up common blocks
            rsave = new double [218];
            isave = new int [37];

            nextcall = 1;
        }
        else {
            // On subsequent calls, restore common blocks
            detail::dsrcom (rsave, isave, 2);            

        }

 
        // Most inputs are just passed through
        // vectors are converted to arrays
        // locally created work arrays are added
        detail::lsode(pf, neq, traits::vector_storage(y), t, tout, itol, rtol, 
            traits::vector_storage(atol), itask, istate,
            iopt, rwork, lrw, iwork, 
            liw, pjac, mf);

        // Save common blocks
        // If we don't do this, need to set parameter istate to 1 before call
        detail::dsrcom (rsave, isave, 1);

        return(1);
    } // lsode, Boost C++ version

    // Compute derivative values after a call to lsode
    int dintdy(double t, int k, int nyh, vector<double> & dky) {
        int iflag;

        detail::dintdy(t, k, &rwork[20], nyh, traits::vector_storage(dky), iflag);

        return(iflag);
    }


}}}} // namespace boost::numeric::bindings::odepack

#endif // BOOST_NUMERIC_BINDINGS_ODEPACK_ODEPACK_HPP
