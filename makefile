#sheblamo
CC=g++
CFLAGS=-Wall -Werror -std=c++0x
#
WKDIR=($(HOME)/programs/csci-2270/project5/)

all: program

program: Assignment5.cpp
	$(CC) $(CFLAGS) Assignment5.cpp MovieTree.cpp MovieTree.h -o Assignment5.o

clean:
	rm *o Assignment5
