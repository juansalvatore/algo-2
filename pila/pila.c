#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

#define PILA_CAPACIDAD 4

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

pila_t *pila_crear(void)
{
    pila_t *pila = malloc(sizeof(pila_t));
    if (pila == NULL)
        return NULL;
    pila->datos = malloc(PILA_CAPACIDAD * sizeof(void *));
    if (pila->datos == NULL)
    {
        free(pila);
        return NULL;
    }
    pila->cantidad = 0;
    pila->capacidad = PILA_CAPACIDAD;
    return pila;
}

void pila_destruir(pila_t *pila)
{
    free(pila->datos);
    free(pila);
}

bool pila_apilar(pila_t *pila, void *valor)
{
    if (pila->cantidad >= PILA_CAPACIDAD)
        pila->datos = realloc(pila->datos, (pila->cantidad + 1) * sizeof(void *));
    if (pila->datos == NULL)
        return false;
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    pila->capacidad++;
    _print_pila(pila);
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
