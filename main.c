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
            almn.prom_notas = 0;

            while (fread(&nBuff, sizeof(Nota), 1, fpN) > 0)
            {
                if (strcmpi(nBuff.dni, almn.p.dni) == 0)
                    almn.prom_notas += nBuff.nota;
            }

            almn.prom_notas /= 2;

            agregarNodoAlPrincipio(lista, almn);

            rewind(fpN);
        }

        fclose(fpN);
        fclose(fpP);
    }
    else
        printf("ERROR DE DATOS\n");
}

void mostrarAlumno (Alumno almn)
{
    printf("ALUMNO: %s\n", almn.p.nombre);
    printf("DNI: %s\n", almn.p.dni);
    printf("EDAD: %i\n", almn.p.edad);
    printf("PROMEDIO NOTAS: %.2f\n\n", almn.prom_notas);
}

void mostrarListaRec (nodo* lista)
{
    if (lista)
    {
        mostrarAlumno(lista->almn);
        mostrarListaRec(lista->sig);
    }
}

void eliminarNodo (nodo** lista, char* dni)
{
    if (*lista)
    {
        nodo* ant = *lista, *act = (*lista)->sig;

        if (strcmpi((*lista)->almn.p.dni, dni) == 0)
        {
            *lista = (*lista)->sig;
            free(ant);
        }
        else
        {
            while (act && strcmpi(act->almn.p.dni, dni) != 0)
            {
                ant = act;
                act = act->sig;
            }

            if (act)
            {
                ant->sig = act->sig;
                free(act);
            }
        }
    }
}

char* retornarDniMenor (nodo* lista)
{
    if (lista)
    {
        nodo* auxEdadM = lista;
        lista = lista->sig;

        while (lista)
        {
            if (lista->almn.p.edad < auxEdadM->almn.p.edad)
                auxEdadM = lista;

            lista = lista->sig;
        }

        return auxEdadM->almn.p.dni;
    }
    else
        return "LISTA VACIA";
}

/// main

int main()
{
    nodo* listaAlumnos;
    inicLista(&listaAlumnos);

    despersistirYAgregar(&listaAlumnos);

    mostrarListaRec(listaAlumnos);

    eliminarNodo(&listaAlumnos, "28546987");

    printf("\nLISTA DESPUES DE BORRAR\n\n");

    mostrarListaRec(listaAlumnos);

    printf("El DNI del alumno de menor edad es: %s\n", retornarDniMenor(listaAlumnos));

    return 0;
}
