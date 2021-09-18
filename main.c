#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void inicLista (nodo** lista)
{
    *lista = NULL;
}

nodo* crearNodo (Alumno almn)
{
    nodo* aux = (nodo*)malloc(sizeof(nodo));
    aux->almn = almn;
    aux->sig = NULL;
    return aux;
}

void agregarNodoAlPrincipio (nodo** lista, Alumno almn)
{
    if (*lista)
    {
        nodo* aux = crearNodo(almn);
        aux->sig = *lista;
        *lista = aux;
    }
    else
        *lista = crearNodo(almn);
}

void despersistirYAgregar (nodo** lista)
{
    FILE* fpP = fopen (archPersonas, "rb");
    FILE* fpN = fopen (archNotas, "rb");

    Persona pBuff;
    Nota nBuff;
    Alumno almn;

    if (fpP && fpN)
    {
        while (fread(&pBuff, sizeof(Persona), 1, fpP) > 0)
        {
            almn.p = pBuff;

            while (fread(&nBuff, sizeof(Nota), 1, fpN) > 0)
            {
                if (strcmpi(nBuff.dni, almn.p.dni) == 0)
                    almn.prom_notas += (float)nBuff.nota / 2;
            }

            agregarNodoAlPrincipio(lista, almn);

            rewind(fpN);
        }

        fclose(fpN);
        fclose(fpP);
    }
    else
        printf("ERROR DE DATOS\n");
}


/// main

int main()
{
    nodo* listaAlumnos;
    inicLista(&listaAlumnos);

    despersistirYAgregar(&listaAlumnos);


    return 0;
}
