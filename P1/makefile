CC=g++
CFLAGS=-g -Iinclude
BIN=bin
OBJ=obj

_EXE=bin/main_exe
_CPP = $(wildcard src/*.cpp))
_OBJ = $(addprefix obj/, $(notdir $(addsuffix .o, $(basename $(_CPP)))))

all: $(_EXE)
	./$(_EXE)

comp: $(_EXE)

depurar: $(_EXE)
	gdb $(_EXE)

$(_EXE): $(_OBJ) makefile
	$(CC) -o $(_EXE) $(_OBJ)

obj/%.o : src/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -r $(OBJ)/* $(_EXE)