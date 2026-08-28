#ifndef ALUMNO_H
#define ALUMNO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int matricula;
    char nombre[60];
    int semestres;
    float promedio;
}Alumno;

Alumno* crearAlumno(int matricula);
void imprimirAlumno(void *dato);
int compararPorMatricula(void *a, void *b);
int compararPorNombre(void *a, void *b);
int compararPorSemestre(void *a, void *b);
int compararPorPromedio(void *a, void *b);

#endif