#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <Nodo.h>

typedef struct
{
	Nodo *inicio;
	Nodo *fin;
	size_t cant;
	Orden orden;
}Lista;

Lista inicializarLista(void);
void imprimirLista(Lista lista,fn_imprimir imprimir);
void eliminarLista(Lista *lista);
void insertarFinal(Lista *lista,void *dato);
void eliminarDato(Lista *lista,void *dato,fn_comparar comparar);
int buscarDato(Lista lista,void *dato,fn_comparar comparar);
void ordenarLista(Lista *lista,fn_comparar comparar,Orden orden);

void insertarOrdenado(Lista *lista, void *dato, fn_comparar comparar);
void *buscarDatoPtr(Lista lista, void *dato, fn_comparar comparar);
void eliminarListaConDatos(Lista *lista, fn_free liberarDato);
#endif