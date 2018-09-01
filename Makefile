SHELL = /bin/sh

TARGET = odepack
DOUBLE_PRECISION = opkda1.o opkda2.o opkdmain.o
SINGLE_PRECISION = opksa1.o opksa2.o opksmain.o

FC = gfortran
FFLAGS = -ffixed-form -std=legacy
# legacy option shuts off warnings about obsolete f77 code

# Use implicit rules to compile the souce .f to object .o

$(TARGET).so: $(DOUBLE_PRECISION)
	gfortran -shared -o lib$(TARGET).so $(DOUBLE_PRECISION)

.PHONY : clean
clean:
	rm -f *.o *.dll *.a *~ core
