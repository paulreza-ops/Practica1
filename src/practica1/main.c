#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostring.h>

#include <Lista.h>
#include "Alumno.h"

int compararInt(void*,void*);
int compararChar(void*,void*);
int compararCadena(void*,void*);
void imprimirInt(void*);
void imprimirCadena(void*);

void mostrarMenu(void);
int seleccionarCriterio(void);
fn_comparar obtenerComparador(int index);

int main(void)
{
    Lista lista = inicializarLista();
    fn_comparar comparadorActual = compararPorMatricula;
    Orden ordenActual = ASCENDENTE;

    int ciclo = 1;
    while(ciclo)
    {
        mostrarMenu();
        unsigned int opcion = 0;
        inputEnteroSinSigno("", &opcion);

        switch(opcion)
        {
            case 1:
            {
                unsigned int matricula = 0;

                inputEnteroSinSigno("Matricula: ", &matricula);
                Alumno aux = { .matricula = matricula };
               
                if(buscarDato(lista, &aux, compararPorMatricula))
                    printf("Error: ya existe un alumno con matricula %u\n", matricula);
                else{
                    Alumno *nuevo = crearAlumno(matricula);
                    insertarOrdenado(&lista, nuevo, comparadorActual);
                    printf("Alumno registrado correctamente\n");
                }
                break;
            }

            case 2:
            {
                imprimirLista(lista, imprimirAlumno);
                break;
            }

            case 3:
            {
                int criterio = seleccionarCriterio();
                comparadorActual = obtenerComparador(criterio);

                printf("Seleccionar direccion, 1=ASCENDENTE, 2=DESCENDENTE\n");
                unsigned int dir = 0;
                inputEnteroSinSigno(": ", &dir);
                ordenActual = (dir == 2) ? DESCENDENTE : ASCENDENTE;

                ordenarLista(&lista, comparadorActual, ordenActual);
                printf("Lista reordenada\n");
                break;
            }

            case 4:
            {
                int criterio = seleccionarCriterio();
                if (criterio == 1)
                {
                    unsigned int matricula = 0;
                    inputEnteroSinSigno("Matricula a buscar: ", &matricula);
                    Alumno alumno_buscado = { .matricula = matricula };
                    Alumno *res = (Alumno*) buscarDatoPtr(lista, &alumno_buscado, compararPorMatricula);
                    if (res) imprimirAlumno(res);
                    else printf("Alumno con matricula %u no encontrado\n", matricula);
                }
                else if (criterio == 2)
                {
                    char nombreBuscar[59] = {0};
                    inputCadena("Nombre a buscar: ", nombreBuscar, sizeof(nombreBuscar));
                    Alumno alumno_buscado = {0};
                    strncpy(alumno_buscado.nombre, nombreBuscar, sizeof(alumno_buscado.nombre)-1);
                    Alumno *res = (Alumno*) buscarDatoPtr(lista, &alumno_buscado, compararPorNombre);
                    if (res) imprimirAlumno(res);
                    else printf("Alumno con nombre '%s' no encontrado\n", nombreBuscar);
                }
                else if (criterio == 3)
                {
                    int sem = 0;
                    inputEntero("Semestres a buscar: ", &sem);
                    Alumno alumno_buscado = { .semestres = sem };
                    Alumno *res = (Alumno*) buscarDatoPtr(lista, &alumno_buscado, compararPorSemestre);
                    if (res) imprimirAlumno(res);
                    else printf("Alumno con %d semestres no encontrado\n", sem);
                }
                else
                {
                    float prom = 0.0f;
                    inputFloat("Promedio a buscar: ", &prom);
                    Alumno alumno_buscado = { .promedio = prom };
                    Alumno *res = (Alumno*) buscarDatoPtr(lista, &alumno_buscado, compararPorPromedio);
                    if (res) imprimirAlumno(res);
                    else printf("Alumno con promedio %.2f no encontrado\n", prom);
                }
                break;
            }

            case 5:
            {
                unsigned int matricula = 0;
                inputEnteroSinSigno("Matricula a borrar: ", &matricula);
                Alumno aux = { .matricula = matricula };
                Alumno *res = (Alumno*) buscarDatoPtr(lista, &aux, compararPorMatricula);
                if(res){
                    printf("Se borro el alumno: \n");
                    imprimirAlumno(res);
                    eliminarDato(&lista, res, compararPorMatricula);
                }
                else
                {
                    printf("No se encontro alumno con matricula %u\n", matricula);
                }
                break;
            }

            case 6:
            {
                eliminarListaConDatos(&lista, free);
                ciclo = 0;
                break;
            }

            default:
                printf("Opcion no valida\n");
                break;
        }
    }

    printf("FIN DEL PROGRAMA \n");
    return 0;
}

int compararInt(void* pa,void* pb)
{
	int a = *(int*)pa;
	int b = *(int*)pb;
	if( a>b) return 1;
	else if(a<b) return -1;
	else return 0;
}


int compararChar(void* a,void* b)
{
	return strcmp((char*)a,(char*)b);
}

void imprimirInt(void *dato)
{
	printf("%d", *(int*)dato);
}

void imprimirCadena(void *dato)
{	
	printf("%s", (char*)dato);
}


int compararCadena(void *a,void *b)
{
	return strcmp(a,b);
}

void mostrarMenu(void)
{
    printf("\n------ Menu ------\n");
    printf("1. Registrar Alumno\n");
    printf("2. Desplegar Alumnos\n");
    printf("3. Reordenar\n");
    printf("4. Buscar Alumno\n");
    printf("5. Borrar Alumno\n");
    printf("6. Finalizar\n");
    printf("Seleccionar una opcion: ");
}

int seleccionarCriterio(void)
{
    printf("Seleccionar criterio:\n");
    printf("1. Matricula\n");
    printf("2. Nombre\n");
    printf("3. Semestres\n");
    printf("4. Promedio\n");
    int opcion = 0;
    inputEntero(": ", &opcion);
    return opcion;
}

fn_comparar obtenerComparador(int index)
{
    switch(index)
    {
        case 1: return compararPorMatricula;
        case 2: return compararPorNombre;
        case 3: return compararPorSemestre;
        case 4: return compararPorPromedio;
        default: return compararPorMatricula;
    }
}