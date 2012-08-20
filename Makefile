.PHONY: clean

teste: main.o opcl.o
	g++ main.o opcl.o  -I../opencl10/CL/cl.h -framework OpenCL -o multi 
	
main.o: main.c opcl.h 
	g++ main.c -Wall -ansi -pedantic -c
	
opcl.o: opcl.c opcl.h
	g++  opcl.c -Wall -ansi -pedantic -c

clean:
	rm -f *.o multi
