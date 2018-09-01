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

#ifndef BOOST_NUMERIC_BINDINGS_ODEPACK_ODEPACK_NAMES_H
#define BOOST_NUMERIC_BINDINGS_ODEPACK_ODEPACK_NAMES_H

#ifndef BOOST_NUMERIC_BINDINGS_USE_CLAPACK
#  include <boost/numeric/bindings/traits/fortran.h>
#else
#  define FORTRAN_ID( id ) id##_
#endif 

#define ODEPACK_DLSODE FORTRAN_ID( dlsode )
#define ODEPACK_SLSODE FORTRAN_ID( slsode )
#define ODEPACK_DSRCOM FORTRAN_ID( dsrcom )
#define ODEPACK_DINTDY FORTRAN_ID( dintdy )

#endif 

