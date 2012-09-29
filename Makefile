.PHONY: clean

teste: main.o opcl.o rk.o
	g++ main.o opcl.o rk.o -I../opencl10/CL/cl.h -framework OpenCL -o rk 
	
main.o: main.c rk.h 
	g++ main.c -Wall -ansi -pedantic -c
	
opcl.o: opcl.c opcl.h
	g++  opcl.c -Wall -ansi -pedantic -c

rk.o: rk.c rk.h opcl.h
	g++ rk.c -Wall -ansi -pedantic -c


clean:
	rm -f *.o rk
