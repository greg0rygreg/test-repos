gcf = -g -Wall -Wextra
gc = clang $(gcf)
ifeq ($(OS),Windows_NT)
	e = .exe
	del = del /q
else
	e = 
	del = rm -f
endif

all: test clean

test: test.o strutils.o
	$(gc) -o test$(e) test.o strutils.o

test.o:
	$(gc) -c test.c -o test.o

strutils.o:
	$(gc) -c strutils.c -o strutils.o

clean:
	$(del) *.o