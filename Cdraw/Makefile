cf = -g -Wall -Wextra
c = clang $(cf)
ifeq ($(OS), Windows_NT)
	del = del /Q
	e = .exe
else
	del = rm -f
	e = 
endif

all: main clean

main: libmenu.o strutils.o main.o
	$(c) -o main libmenu.o strutils.o main.o

main.o:
	$(c) -c main.c

libmenu.o:
	$(c) -c libmenu.c

strutils.o:
	$(c) -c strutils.c

clean:
	$(del) *.o
