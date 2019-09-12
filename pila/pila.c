#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

#define PILA_CAPACIDAD_INICIAL 20

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila
{
    void **datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad; // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/
void _print_pila(const pila_t *pila)
{
    printf("%ld: %d\n", pila->cantidad - 1, *(int *)pila_ver_tope(pila));
}

void _pila_resize(pila_t *pila, double factor)
{
    size_t nueva_capacidad = (size_t)((double)pila->capacidad * factor);
    pila->datos = realloc(pila->datos, nueva_capacidad * sizeof(void *));
    pila->capacidad = nueva_capacidad;
}

pila_t *pila_crear(void)
{
    pila_t *pila = malloc(sizeof(pila_t));
    if (pila == NULL)
        return NULL;
    pila->datos = malloc(PILA_CAPACIDAD_INICIAL * sizeof(void *));
    if (pila->datos == NULL)
    {
        free(pila);
        return NULL;
    }
    pila->cantidad = 0;
    pila->capacidad = PILA_CAPACIDAD_INICIAL;
    return pila;
}

void pila_destruir(pila_t *pila)
{
    free(pila->datos);
    free(pila);
}

bool pila_apilar(pila_t *pila, void *valor)
{
    if (pila->cantidad >= pila->capacidad)
        _pila_resize(pila, 2);
    if (pila->datos == NULL)
        return false;
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

bool pila_esta_vacia(const pila_t *pila)
{
    return pila->cantidad == 0 ? true : false;
}

void *pila_ver_tope(const pila_t *pila)
{
    return pila_esta_vacia(pila) ? NULL : pila->datos[pila->cantidad - 1];
}

void *pila_desapilar(pila_t *pila)
{
    if (pila_esta_vacia(pila))
        return NULL;
    void *tope = pila_ver_tope(pila);
    pila->cantidad--;
    if (pila->cantidad <= pila->capacidad / 2)
        _pila_resize(pila, 0.5);
    return tope;
}
