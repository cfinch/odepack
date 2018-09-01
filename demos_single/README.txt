This folder contains demonstration codes to exercise the single-precision 
routines in odepack.  I haven't gotten around to splitting the text file into
source code and documentation, or building a Makefile.

Before building them, go to the parent directory and build the library by 
typing "make".  These demo programs assume that the shared library 
"libodepack.so" can be found in the parent directory, and they will not run
if it is not there.  If you install libodepack in the standard library search
path of your system, you should be able to run the demos anywhere.  Of course, 
all this can be changed in the Makefile.

   Craig Finch
   September 2007
