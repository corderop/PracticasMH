CC=g++
CFLAGS=-g -Iinclude
BIN=bin
OBJ=obj

_EXE=bin/main_exe
_CPP = $(wildcard src/*.cpp))
_OBJ = $(addprefix obj/, $(notdir $(addsuffix .o, $(basename $(_CPP)))))

all: $(_EXE)

depurar: $(_EXE)
	gdb $(_EXE)

$(_EXE): $(_OBJ) makefile
	$(CC) -o $(_EXE) $(_OBJ)

obj/%.o : src/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

valgrind: $(_EXE)
	valgrind -v --tool=memcheck --leak-check=full --track-origins=yes --show-reachable=yes ./$(_EXE)

clean:
	rm -r $(OBJ)/* $(_EXE)

##########################################
# Ejecuciones de prueba con semilla cualquiera ( según el tiempo actual )
##########################################

# GREEDY

greedy_rand: $(_EXE)
	$(_EXE) g rand 10

greedy_iris: $(_EXE)
	$(_EXE) g iris 10

greedy_ecoli: $(_EXE)
	$(_EXE) g ecoli 10

# Búsqueda local

bl_rand: $(_EXE)
	$(_EXE) bl rand 10

bl_iris: $(_EXE)
	$(_EXE) bl iris 10

bl_ecoli: $(_EXE)
	$(_EXE) bl ecoli 10

##########################################
# Extración de datos para tablas		
##########################################
greedy_data: $(_EXE)
	echo -e "RAND10 ----------------" > salidaGreedy
	./$(_EXE) g rand 10 120 >> salidaGreedy
	./$(_EXE) g rand 10 4350 >> salidaGreedy
	./$(_EXE) g rand 10 549 >> salidaGreedy
	./$(_EXE) g rand 10 7581 >> salidaGreedy
	./$(_EXE) g rand 10 679 >> salidaGreedy
	echo -e "IRIS10 ----------------" >> salidaGreedy
	./$(_EXE) g iris 10 120 >> salidaGreedy
	./$(_EXE) g iris 10 876 >> salidaGreedy
	./$(_EXE) g iris 10 549 >> salidaGreedy
	./$(_EXE) g iris 10 7581 >> salidaGreedy
	./$(_EXE) g iris 10 679 >> salidaGreedy
	echo -e "ECOLI10 ----------------" >> salidaGreedy
	./$(_EXE) g ecoli 10 120 >> salidaGreedy
	./$(_EXE) g ecoli 10 876 >> salidaGreedy
	./$(_EXE) g ecoli 10 549 >> salidaGreedy
	./$(_EXE) g ecoli 10 7581 >> salidaGreedy
	./$(_EXE) g ecoli 10 679 >> salidaGreedy
	echo -e "RAND20 ----------------" >> salidaGreedy
	./$(_EXE) g rand 20 120 >> salidaGreedy
	./$(_EXE) g rand 20 876 >> salidaGreedy
	./$(_EXE) g rand 20 549 >> salidaGreedy
	./$(_EXE) g rand 20 7581 >> salidaGreedy
	./$(_EXE) g rand 20 679 >> salidaGreedy
	echo -e "IRIS20 ----------------" >> salidaGreedy
	./$(_EXE) g iris 20 120 >> salidaGreedy
	./$(_EXE) g iris 20 876 >> salidaGreedy
	./$(_EXE) g iris 20 549 >> salidaGreedy
	./$(_EXE) g iris 20 7581 >> salidaGreedy
	./$(_EXE) g iris 20 679 >> salidaGreedy
	echo -e "ECOLI20 ----------------" >> salidaGreedy
	./$(_EXE) g ecoli 20 120 >> salidaGreedy
	./$(_EXE) g ecoli 20 876 >> salidaGreedy
	./$(_EXE) g ecoli 20 549 >> salidaGreedy
	./$(_EXE) g ecoli 20 7581 >> salidaGreedy
	./$(_EXE) g ecoli 20 679 >> salidaGreedy

bl_data: $(_EXE)
	echo -e "RAND10 ----------------" > salidaBL
	./$(_EXE) bl rand 10 120 >> salidaBL
	./$(_EXE) bl rand 10 876 >> salidaBL
	./$(_EXE) bl rand 10 549 >> salidaBL
	./$(_EXE) bl rand 10 7581 >> salidaBL
	./$(_EXE) bl rand 10 679 >> salidaBL
	echo -e "IRIS10 ----------------" >> salidaBL
	./$(_EXE) bl iris 10 120 >> salidaBL
	./$(_EXE) bl iris 10 876 >> salidaBL
	./$(_EXE) bl iris 10 549 >> salidaBL
	./$(_EXE) bl iris 10 7581 >> salidaBL
	./$(_EXE) bl iris 10 679 >> salidaBL
	echo -e "ECOLI10 ----------------" >> salidaBL
	./$(_EXE) bl ecoli 10 120 >> salidaBL
	./$(_EXE) bl ecoli 10 876 >> salidaBL
	./$(_EXE) bl ecoli 10 549 >> salidaBL
	./$(_EXE) bl ecoli 10 7581 >> salidaBL
	./$(_EXE) bl ecoli 10 679 >> salidaBL
	echo -e "RAND20 ----------------" >> salidaBL
	./$(_EXE) bl rand 20 120 >> salidaBL
	./$(_EXE) bl rand 20 876 >> salidaBL
	./$(_EXE) bl rand 20 549 >> salidaBL
	./$(_EXE) bl rand 20 7581 >> salidaBL
	./$(_EXE) bl rand 20 679 >> salidaBL
	echo -e "IRIS20 ----------------" >> salidaBL
	./$(_EXE) bl iris 20 120 >> salidaBL
	./$(_EXE) bl iris 20 876 >> salidaBL
	./$(_EXE) bl iris 20 549 >> salidaBL
	./$(_EXE) bl iris 20 7581 >> salidaBL
	./$(_EXE) bl iris 20 679 >> salidaBL
	echo -e "ECOLI20 ----------------" >> salidaBL
	./$(_EXE) bl ecoli 20 120 >> salidaBL
	./$(_EXE) bl ecoli 20 876 >> salidaBL
	./$(_EXE) bl ecoli 20 549 >> salidaBL
	./$(_EXE) bl ecoli 20 7581 >> salidaBL
	./$(_EXE) bl ecoli 20 679 >> salidaBL