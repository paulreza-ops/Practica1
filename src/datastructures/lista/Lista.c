#include "Lista.h"

Lista inicializarLista(void)
{
	return (Lista){.inicio=NULL,.fin=NULL,.cant=0,.orden=NINGUNO};
}

void imprimirLista(Lista lista,fn_imprimir imprimir)
{
	Nodo *aux;
	if(!lista.inicio)
	{
		printf("\n Lista vacia");
		return;
	}	
	printf("\n [CANT %llu] Lista: \n ",lista.cant);
	aux = lista.inicio;
	while( aux )
	{
		imprimir(aux->dato);
		printf(" \n ");
		aux = aux->sig;
	}
}

void eliminarLista(Lista *lista)
{
	if( !lista->inicio) return;
	Nodo *aux;
	while( lista->inicio)
	{
		aux = lista->inicio;
		lista->inicio = lista->inicio->sig;
		free(aux);
	}
	lista->fin = lista->inicio;
	lista->cant = 0;
}

void insertarFinal(Lista *lista,void *dato)
{
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = crearNodo(dato);
		lista->cant++;
		return;
	}
	lista->fin->sig = crearNodo(dato);
	lista->fin = lista->fin->sig;
	lista->cant++;
}

void eliminarDato(Lista *lista,void *dato,fn_comparar comparar)
{	
	if(!lista->inicio)
		return;
	
	for(Nodo *ant=NULL,*elim=lista->inicio ; elim ; ant = elim , elim = elim->sig)
	{
		if( comparar( dato , elim->dato ) == 0)
		{
			if( lista->inicio == elim)
				lista->inicio = elim->sig;
			else
				ant->sig = elim->sig;
			if( lista->fin == elim)
				lista->fin = ant;
			free(elim);
			lista->cant--;
			return;
		}
	}	
}

int buscarDato(Lista lista,void *dato,fn_comparar comparar)
{
	if(!lista.inicio)
		return 0;
	while(lista.inicio)
	{
		if(comparar( dato, lista.inicio->dato ) == 0)
			return 1;
		lista.inicio = lista.inicio->sig;
	}
	
	return 0;
}

void ordenarLista(Lista *lista,fn_comparar comparar,Orden orden)
{
	lista->orden = orden;
	if(orden == NINGUNO)
		return;
	for( Nodo *i = lista->inicio ; i ; i = i->sig)
	{
		Nodo *cmp = i;
		for( Nodo *j = i->sig ; j ; j = j->sig)
		{
			if(orden == ASCENDENTE && comparar(cmp->dato,j->dato)>0)
				cmp = j;
			else if(orden == DESCENDENTE && comparar(cmp->dato,j->dato)<0)
				cmp = j;			
		}
		if(cmp!=i)
			swapNodo(i,cmp);
	}
}

void insertarOrdenado(Lista *lista, void *dato, fn_comparar comparar){
	Nodo *nuevo = crearNodo(dato);
	Nodo *actual;

	if(!lista->inicio){
		lista->inicio = lista->fin = nuevo;
		lista->cant++;
		return;
	}

	if(comparar(dato, lista->inicio->dato) < 0){
		nuevo->sig = lista->inicio;
		lista->inicio = nuevo;
		lista->cant++;
		return;
	}

	for(actual = lista->inicio; actual->sig && comparar(dato, actual->sig->dato) >= 0; actual = actual->sig);

	nuevo->sig = actual->sig;
	actual->sig = nuevo;

	if(!nuevo->sig)
		lista->fin = nuevo;

	lista->cant++;
}

void *buscarDatoPtr(Lista lista, void *dato, fn_comparar comparar)
{
    if (!lista.inicio)
        return NULL;

    Nodo *aux = lista.inicio;
    while (aux)
    {
        if (comparar(dato, aux->dato) == 0)
            return aux->dato;
        aux = aux->sig;
    }
    return NULL;
}

void eliminarListaConDatos(Lista *lista, fn_free liberarDato)
{
    if (!lista->inicio)
        return;

    Nodo *aux = lista->inicio;
    while (aux)
    {
        Nodo *sig = aux->sig;
        if (liberarDato && aux->dato)
            liberarDato(aux->dato);
        free(aux);
        aux = sig;
    }
    lista->inicio = lista->fin = NULL;
    lista->cant = 0;
    lista->orden = NINGUNO;
}