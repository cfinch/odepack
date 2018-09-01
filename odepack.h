/*
 * 
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
 */

#ifndef BOOST_NUMERIC_BINDINGS_ODEPACK_ODEPACK_H
#define BOOST_NUMERIC_BINDINGS_ODEPACK_ODEPACK_H

#include "odepack_names.h"

#ifndef BOOST_NUMERIC_BINDINGS_NO_STRUCTURE_CHECK 
#  define BOOST_NUMERIC_BINDINGS_FORTRAN
#endif 

extern "C" {

    // double precision solution of system of ODEs
    void ODEPACK_DLSODE (void (*pf)(int* neq, double* t, double* y, double* ydot),
            int const* neq, double* y,
            double* t, double const * tout, int const* itol, double const* rtol,
            double const* atol, int const* itask, int* istate,
            int const* iopt, double* rwork, int const* lrw, int* iwork,
            int const* liw, 
            void (*pjac)(int* neq, double* t, double* y, int* ml, int* mu, double* pd, int* nrowpd),
            int const* mf);

    // single precision solution of system of ODEs
    void ODEPACK_SLSODE (void (*pf)(int* neq, float* t, float* y, float* ydot),
            int const* neq, float* y,
            float* t, float const * tout, int const* itol, float const* rtol,
            float const* atol, int const* itask, int* istate,
            int const* iopt, float* rwork, int const* lrw, int* iwork,
            int const* liw, 
            void (*pjac)(int* neq, float* t, float* y, int* ml, int* mu, float* pd, int* nrowpd),
            int const* mf);

    // save common block information
    void ODEPACK_DSRCOM (double * rsav, int * isav, int * job);

    // compute derivatives
    void ODEPACK_DINTDY (double * t, int * k, double * rwork21,
        int * nyh, double * dky, int * iflag);

}
#endif
