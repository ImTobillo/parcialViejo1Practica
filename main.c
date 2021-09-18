#include <stdio.h>
#include <stdlib.h>
#define archPersonas "Personas.dat"
#define archNotas "notas.dat"

/// estructuras

typedef struct
{
    char nombre[20];
    int edad;
    char dni[9];
}Persona;

typedef struct
{
    char dni[9];
    int nota;
}Nota;

typedef struct
{
    Persona p;
    float prom_notas;
}Alumno;

typedef struct nodo
{
    Alumno almn;
    struct nodo* sig;
}nodo;

/// funciones

nodo* crearNodo (Alumno almn)
{
    nodo* aux = (nodo*)malloc(sizeof(nodo));
    aux->almn = almn;
    aux->sig = NULL;
    return aux;
}

void agregarNodo (nodo** lista, Alumno almn)
{
    if (*lista)
    {
        nodo* aux = *lista;

        while (aux->sig)
            aux = aux->sig;

        aux->sig = crearNodo(almn);
    }
    else
        *lista = crearNodo(almn);
}

void despersistirYAgregar (nodo** lista)
{
    FILE* fpP = fopen (archPersonas, "rb");
    FILE* fpN = fopen (archNotas, "rb");

    if ()


}


/// main

int main()
{



    return 0;
}
