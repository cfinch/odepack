This folder contains a C version of the example program found in the source
code comments for the routine "dlsode".  

It doesn't work because I made some changes in the experimental Boost C++
interface, and I haven't gotten around to fixing them.

When run, it should produce the results shown in the file called
"expected_results.txt".

Before building it, go to the parent directory and build the library by 
typing "make".  This example program assumes that the shared library 
"libodepack.so" can be found in the parent directory, and it will not run 
if the library is not there.  If you install libodepack in the standard
library search path of your system, you should be able to run the example 
anywhere.  Of course, all this can be changed in the Makefile.

   Craig Finch
   September 2007
