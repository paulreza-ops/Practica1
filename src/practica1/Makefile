cflags = -Wall -Werror -std=c99 -O2
includes = -I ../iostring -I ../datastructures/nodo -I ../datastructures/lista
libs = ../../lib -liostring -lLista
source = $(wildcard *.c) 
output = ../../bin/practica1

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
run:
	$(output)
rebuild:
	make -C ..\iostring
	make -C ..\datastructures\nodo
	make -C ..\datastructures\lista
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"