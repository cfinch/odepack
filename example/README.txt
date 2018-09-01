This folder contains the example program found in the source code comments for
the routine "dlsode".  I partially updated it to Fortran 95 syntax so it would
be easier to read.  When run, it should produce the results shown in the file called
"expected_results.txt".

Before building it, go to the parent directory and
build the library by typing "make".  This example program assumes that the
shared library "libodepack.so" can be found in the parent directory, and it
will not run if the library is not there.  If you install libodepack in the standard
library search path of your system, you should be able to run the example anywhere.
Of course, all this can be changed in the Makefile.

   Craig Finch
   September 2007
