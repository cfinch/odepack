# A Re-Distribution of ODEPACK

This is a re-distribution of ODEPACK.  The original distribution can be found
at http://www.netlib.org/odepack/  I found the original distribution to be
very confusing for a beginner to use--especially someone who is not familiar
with Fortran 77.  However, ODEPACK is a very useful tool that should be 
accessible to everyone.  I have taken the initiative to reorganize ODEPACK
into a more "modern" distribution that is better organized and easy to
understand.  I moved some things around, created GNU Makefiles, and moved the
documentation into .html documents for easier navigation (previously, it was
embedded in the source code).

IMPORTANT--I did not write any of the numerical code in ODEPACK, nor did I
modify it, and I am not making any claim to have done so.  The copyright
remains with the original authors.  I also make no guarantees about the
suitability of the code or distribution for any purpose, and ODEPACK comes
with NO WARRANTY of any kind.

My only original contribution is to create a prototype of a BOOST interface,
modelled after the BOOST-LAPACK interface.  It is in no way complete, and you
use it at your own risk.

I recognize that many things about this distribution can be improved, and I
welcome feedback, suggestions, and contributions.

   Craig Finch
   cfinch@ieee.org
   September 2007
