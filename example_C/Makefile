# Name of the file(s) we're compiling

TARGET = example

# location of the Boost Python include files and library
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib
ODEPACK = ..

$(TARGET).so: $(TARGET).o
	g++ -Wl,--export-dynamic -Wl,-rpath,.. \
	$(TARGET).o -L$(BOOST_LIB) -L$(ODEPACK) \
	-lodepack \
	-o $(TARGET)

$(TARGET).o: $(TARGET).C ../odepack.hpp ../odepack.h ../odepack_names.h
	g++ -I$(BOOST_INC) -I$(ODEPACK) -c $(TARGET).C

.PHONY: clean

clean:
	rm -f *.o *.dll *.a *~ core
