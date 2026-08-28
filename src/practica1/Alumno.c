#include "Alumno.h"
#include <iostring.h>

Alumno* crearAlumno(int matricula){
    Alumno *nuevo = calloc(1,sizeof(Alumno));

    nuevo->matricula = matricula;
    inputCadena("Nombre: ", nuevo->nombre, sizeof(nuevo->nombre));
    inputEntero("Semestres: ", &nuevo->semestres);
    inputFloat("Promedio: ", &nuevo->promedio);

    return nuevo;
}

void imprimirAlumno(void *dato){
    Alumno *a = (Alumno*)dato;
    printf("%-6d | %-20s | %-2d | %.2f", a->matricula, a->nombre, a->semestres, a->promedio);
}

int compararPorMatricula(void *a, void *b){
    Alumno *alumnoA = (Alumno*)a;
    Alumno *alumnoB = (Alumno*)b;

    if(alumnoA->matricula > alumnoB->matricula) return 1;
    if(alumnoA->matricula < alumnoB->matricula) return -1;
    return 0;
}

int compararPorNombre(void *a, void *b){
    Alumno *alumnoA = (Alumno*)a;
    Alumno *alumnoB = (Alumno*)b;
    return strcmp(alumnoA->nombre, alumnoB->nombre);
}

int compararPorSemestre(void *a, void *b){
    Alumno *alumnoA = (Alumno*)a;
    Alumno *alumnoB = (Alumno*)b;

    if(alumnoA->semestres > alumnoB->semestres) return 1;
    if(alumnoA->semestres < alumnoB->semestres) return -1;
    return 0;
}

int compararPorPromedio(void *a, void *b){
    Alumno *alumnoA = (Alumno*)a;
    Alumno *alumnoB = (Alumno*)b;

    if(alumnoA->promedio > alumnoB->promedio) return 1;
    if(alumnoA->promedio < alumnoB->promedio) return -1;
    return 0;
}