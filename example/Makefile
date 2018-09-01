SHELL = /bin/sh

FC = gfortran
FFLAGS = -ffixed-form

# Use implicit rules to compile the souce .f to object .o

example: example.o
	gfortran -Wl,-rpath,.. -L.. -lodepack -o example example.f95

example.o: example.f95
	gfortran -c example.f95

.PHONY : clean

clean:
	rm -f *.o *.dll *.a *~ core
