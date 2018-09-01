SHELL = /bin/sh

FC = gfortran
FFLAGS = -ffixed-form -std=legacy

# Use implicit rules to compile the souce .f to object .o

PROGRAMS = test_lsoda test_lsodar test_lsode test_lsodes test_lsodi test_lsodis test_lsodkr test_lsodpk test_lsoibt

.PHONY : programs $(PROGRAMS)

programs: $(PROGRAMS)

$(PROGRAMS):
	gfortran -Wl,-rpath,.. -L.. -lodepack -o $@ $@.f

.PHONY : clean
clean:
	rm -f *.o *.dll *.a *~ core
