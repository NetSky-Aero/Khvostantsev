all: prog

prog: report.o temp_function.o
	gcc -std=c99 -o prog report.o temp_function.o

report.o: report.c temp_function.h
	gcc -std=c99 -c -o report.o report.c

temp_function.o: temp_function.c
	gcc -std=c99 -c -o temp_function.o temp_function.c

clean:
	del *.o prog.exe  