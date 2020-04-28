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

greedy_newthyroid: $(_EXE)
	$(_EXE) g newthyroid 10

# Búsqueda local

bl_rand: $(_EXE)
	$(_EXE) bl rand 10

bl_iris: $(_EXE)
	$(_EXE) bl iris 10

bl_ecoli: $(_EXE)
	$(_EXE) bl ecoli 10

bl_newthyroid: $(_EXE)
	$(_EXE) bl newthyroid 10

# Búsqueda basada en poblaciones

p_rand: $(_EXE)
	$(_EXE) p rand 10

p_iris: $(_EXE)
	$(_EXE) p iris 10

p_ecoli: $(_EXE)
	$(_EXE) p ecoli 10

p_newthyroid: $(_EXE)
	$(_EXE) p newthyroid 10

##########################################
# Extración de datos para tablas		
##########################################
greedy_data: $(_EXE)
	echo -e "RAND10 ----------------" > salidaGreedy
	./$(_EXE) g rand 10 148 >> salidaGreedy
	./$(_EXE) g rand 10 876 >> salidaGreedy
	./$(_EXE) g rand 10 8942 >> salidaGreedy
	./$(_EXE) g rand 10 4526 >> salidaGreedy
	./$(_EXE) g rand 10 3214 >> salidaGreedy
	echo -e "IRIS10 ----------------" >> salidaGreedy
	./$(_EXE) g iris 10 148 >> salidaGreedy
	./$(_EXE) g iris 10 876 >> salidaGreedy
	./$(_EXE) g iris 10 8942 >> salidaGreedy
	./$(_EXE) g iris 10 4526 >> salidaGreedy
	./$(_EXE) g iris 10 3214 >> salidaGreedy
	echo -e "ECOLI10 ----------------" >> salidaGreedy
	./$(_EXE) g ecoli 10 148 >> salidaGreedy
	./$(_EXE) g ecoli 10 876 >> salidaGreedy
	./$(_EXE) g ecoli 10 8942 >> salidaGreedy
	./$(_EXE) g ecoli 10 4526 >> salidaGreedy
	./$(_EXE) g ecoli 10 3214 >> salidaGreedy
	echo -e "NEWTHYROID10 ----------------" >> salidaGreedy
	./$(_EXE) g newthyroid 10 148 >> salidaGreedy
	./$(_EXE) g newthyroid 10 876 >> salidaGreedy
	./$(_EXE) g newthyroid 10 8942 >> salidaGreedy
	./$(_EXE) g newthyroid 10 4526 >> salidaGreedy
	./$(_EXE) g newthyroid 10 3214 >> salidaGreedy
	echo -e "RAND20 ----------------" >> salidaGreedy
	./$(_EXE) g rand 20 148 >> salidaGreedy
	./$(_EXE) g rand 20 876 >> salidaGreedy
	./$(_EXE) g rand 20 8942 >> salidaGreedy
	./$(_EXE) g rand 20 4526 >> salidaGreedy
	./$(_EXE) g rand 20 3214 >> salidaGreedy
	echo -e "IRIS20 ----------------" >> salidaGreedy
	./$(_EXE) g iris 20 148 >> salidaGreedy
	./$(_EXE) g iris 20 876 >> salidaGreedy
	./$(_EXE) g iris 20 8942 >> salidaGreedy
	./$(_EXE) g iris 20 4526 >> salidaGreedy
	./$(_EXE) g iris 20 3214 >> salidaGreedy
	echo -e "ECOLI20 ----------------" >> salidaGreedy
	./$(_EXE) g ecoli 20 148 >> salidaGreedy
	./$(_EXE) g ecoli 20 876 >> salidaGreedy
	./$(_EXE) g ecoli 20 8942 >> salidaGreedy
	./$(_EXE) g ecoli 20 4526 >> salidaGreedy
	./$(_EXE) g ecoli 20 3214 >> salidaGreedy
	echo -e "NEWTHYROID20 ----------------" >> salidaGreedy
	./$(_EXE) g newthyroid 20 148 >> salidaGreedy
	./$(_EXE) g newthyroid 20 876 >> salidaGreedy
	./$(_EXE) g newthyroid 20 8942 >> salidaGreedy
	./$(_EXE) g newthyroid 20 4526 >> salidaGreedy
	./$(_EXE) g newthyroid 20 3214 >> salidaGreedy

bl_data: $(_EXE)
	echo -e "RAND10 ----------------" > salidaBL
	./$(_EXE) bl rand 10 148 >> salidaBL
	./$(_EXE) bl rand 10 876 >> salidaBL
	./$(_EXE) bl rand 10 8942 >> salidaBL
	./$(_EXE) bl rand 10 4526 >> salidaBL
	./$(_EXE) bl rand 10 3214 >> salidaBL
	echo -e "IRIS10 ----------------" >> salidaBL
	./$(_EXE) bl iris 10 148 >> salidaBL
	./$(_EXE) bl iris 10 876 >> salidaBL
	./$(_EXE) bl iris 10 8942 >> salidaBL
	./$(_EXE) bl iris 10 4526 >> salidaBL
	./$(_EXE) bl iris 10 3214 >> salidaBL
	echo -e "ECOLI10 ----------------" >> salidaBL
	./$(_EXE) bl ecoli 10 148 >> salidaBL
	./$(_EXE) bl ecoli 10 876 >> salidaBL
	./$(_EXE) bl ecoli 10 8942 >> salidaBL
	./$(_EXE) bl ecoli 10 4526 >> salidaBL
	./$(_EXE) bl ecoli 10 3214 >> salidaBL
	echo -e "NEWTHYROID10 ----------------" >> salidaBL
	./$(_EXE) bl newthyroid 10 148 >> salidaBL
	./$(_EXE) bl newthyroid 10 876 >> salidaBL
	./$(_EXE) bl newthyroid 10 8942 >> salidaBL
	./$(_EXE) bl newthyroid 10 4526 >> salidaBL
	./$(_EXE) bl newthyroid 10 3214 >> salidaBL
	echo -e "RAND20 ----------------" >> salidaBL
	./$(_EXE) bl rand 20 148 >> salidaBL
	./$(_EXE) bl rand 20 876 >> salidaBL
	./$(_EXE) bl rand 20 8942 >> salidaBL
	./$(_EXE) bl rand 20 4526 >> salidaBL
	./$(_EXE) bl rand 20 3214 >> salidaBL
	echo -e "IRIS20 ----------------" >> salidaBL
	./$(_EXE) bl iris 20 148 >> salidaBL
	./$(_EXE) bl iris 20 876 >> salidaBL
	./$(_EXE) bl iris 20 8942 >> salidaBL
	./$(_EXE) bl iris 20 4526 >> salidaBL
	./$(_EXE) bl iris 20 3214 >> salidaBL
	echo -e "ECOLI20 ----------------" >> salidaBL
	./$(_EXE) bl ecoli 20 148 >> salidaBL
	./$(_EXE) bl ecoli 20 876 >> salidaBL
	./$(_EXE) bl ecoli 20 8942 >> salidaBL
	./$(_EXE) bl ecoli 20 4526 >> salidaBL
	./$(_EXE) bl ecoli 20 3214 >> salidaBL
	echo -e "NEWTHYROID20 ----------------" >> salidaBL
	./$(_EXE) bl newthyroid 20 148 >> salidaBL
	./$(_EXE) bl newthyroid 20 876 >> salidaBL
	./$(_EXE) bl newthyroid 20 8942 >> salidaBL
	./$(_EXE) bl newthyroid 20 4526 >> salidaBL
	./$(_EXE) bl newthyroid 20 3214 >> salidaBL

p_data: $(_EXE)
	# echo -e "RAND10 ----------------" > salidaP
	# ./$(_EXE) p rand 10 148 >> salidaP
	# ./$(_EXE) p rand 10 876 >> salidaP
	# ./$(_EXE) p rand 10 8942 >> salidaP
	# ./$(_EXE) p rand 10 4526 >> salidaP
	# ./$(_EXE) p rand 10 3214 >> salidaP
	# echo -e "IRIS10 ----------------" >> salidaP
	# ./$(_EXE) p iris 10 148 >> salidaP
	# ./$(_EXE) p iris 10 876 >> salidaP
	# ./$(_EXE) p iris 10 8942 >> salidaP
	# ./$(_EXE) p iris 10 4526 >> salidaP
	# ./$(_EXE) p iris 10 3214 >> salidaP
	# echo -e "ECOLI10 ----------------" >> salidaP
	# ./$(_EXE) p ecoli 10 148 >> salidaP
	# ./$(_EXE) p ecoli 10 876 >> salidaP
	# ./$(_EXE) p ecoli 10 8942 >> salidaP
	# ./$(_EXE) p ecoli 10 4526 >> salidaP
	# ./$(_EXE) p ecoli 10 3214 >> salidaP
	# echo -e "NEWTHYROID10 ----------------" >> salidaP
	# ./$(_EXE) p newthyroid 10 148 >> salidaP
	# ./$(_EXE) p newthyroid 10 876 >> salidaP
	# ./$(_EXE) p newthyroid 10 8942 >> salidaP
	# ./$(_EXE) p newthyroid 10 4526 >> salidaP
	# ./$(_EXE) p newthyroid 10 3214 >> salidaP
	echo -e "RAND20 ----------------" > salidaP
	./$(_EXE) p rand 20 148 >> salidaP
	./$(_EXE) p rand 20 876 >> salidaP
	./$(_EXE) p rand 20 8942 >> salidaP
	./$(_EXE) p rand 20 4526 >> salidaP
	./$(_EXE) p rand 20 3214 >> salidaP
	echo -e "IRIS20 ----------------" >> salidaP
	./$(_EXE) p iris 20 148 >> salidaP
	./$(_EXE) p iris 20 876 >> salidaP
	./$(_EXE) p iris 20 8942 >> salidaP
	./$(_EXE) p iris 20 4526 >> salidaP
	./$(_EXE) p iris 20 3214 >> salidaP
	echo -e "ECOLI20 ----------------" >> salidaP
	./$(_EXE) p ecoli 20 148 >> salidaP
	./$(_EXE) p ecoli 20 876 >> salidaP
	./$(_EXE) p ecoli 20 8942 >> salidaP
	./$(_EXE) p ecoli 20 4526 >> salidaP
	./$(_EXE) p ecoli 20 3214 >> salidaP
	echo -e "NEWTHYROID20 ----------------" >> salidaP
	./$(_EXE) p newthyroid 20 148 >> salidaP
	./$(_EXE) p newthyroid 20 876 >> salidaP
	./$(_EXE) p newthyroid 20 8942 >> salidaP
	./$(_EXE) p newthyroid 20 4526 >> salidaP
	./$(_EXE) p newthyroid 20 3214 >> salidaP