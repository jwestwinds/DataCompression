## CS130 Fall 2013: Computer Graphics
## Lab 2 Makefile
##
## This file does not need to be modified
#########################################
all: decomp datacomp
decomp: decomp.cpp
	g++ -ggdb decomp.cpp -o dec
datacomp: datacomp.cpp
	g++ -ggdb datacomp.cpp -o dac
clean:
	rm -f *~ *.o *.out binary.cpp char.cpp output.cpp dac dec
