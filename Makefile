## CS130 Fall 2013: Computer Graphics
## Lab 2 Makefile
##
## This file does not need to be modified
#########################################

decomp: decomp.o
        g++ -ggdb decomp.o –o decomp
datacomp: datacomp.o
        g++ -ggdb datacomp.o –o datacomp
decomp.o: decomp.cpp
	g++ -ggdb -c decomp.cpp 
datacomp.o: datacomp.cpp
	g++ -ggdb -c datacomp.cpp

clean:
	rm -f *~ *.o *.out binary.cpp char.cpp output.cpp
