#include "heap.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM_INICIAL 20
// buscar como esta en la pila
#define EXPANDIR 2
#define REDUCIR 0.5
#define CRITERIO_REDUCCION 4

/***************************
 * structs
***************************/
struct heap
{
    void **datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

/***************************
 * Funciones auxiliares
***************************/
void swap(void *x, void *y)
{
    void *aux = x;
    x = y;
    y = aux;
}

size_t indice_hijo_izquierdo(size_t i)
{
    return 2 * i + 1;
}

size_t indice_hijo_derecho(size_t i)
{
    return 2 * i + 2;
}

size_t indice_padre(size_t i)
{
    return (i - 1) / 2;
}

bool upHeap(heap_t *heap, size_t i)
{
    if (heap->cant == 0)
        return true;
    size_t i_padre = indice_padre(heap->cant);
    void *elem_actual = heap->datos[heap->cant];
    if (heap->cmp(elem_actual, heap->datos[i_padre]) > 0)
    {
        void *aux = elem_actual;
        heap->datos[heap->cant] = heap->datos[i_padre];
        heap->datos[i_padre] = aux;
    }
    else
    {
        return true;
    }
    return upHeap(heap, i_padre);
}

void downHeap(heap_t *heap, size_t i)
{
    if (i >= heap->cant)
        return;

    void *elem_actual = heap->datos[i];
    size_t i_max = i;
    size_t i_hijo_izq = indice_hijo_izquierdo(i);
    size_t i_hijo_der = indice_hijo_derecho(i);

    if (i_hijo_izq < heap->cant && heap->cmp(heap->datos[i_hijo_izq], heap->datos[i_max]) > 0)
        i_max = i_hijo_izq;
    if (i_hijo_der < heap->cant && heap->cmp(heap->datos[i_hijo_der], heap->datos[i_max]) > 0)
        i_max = i_hijo_izq;
    if (i_max != i)
    {
        void *aux = elem_actual;
        heap->datos[i_max] = elem_actual;
        heap->datos[i] = aux;
        downHeap(heap, i_max);
    }
}

void heapify()
{
}

bool realloc_heap(heap_t *heap, size_t nueva_capacidad)
{
    void *redimension = realloc(heap->datos, nueva_capacidad * sizeof(void *));
    if (redimension == NULL)
        return false;
    heap->datos = redimension;
    heap->tam = nueva_capacidad;
    return true;
}

bool redimension(heap_t *heap)
{
    if (heap->cant == heap->tam)
        return realloc_heap(heap, (heap->tam * EXPANDIR));

    if (heap->cant <= (heap->tam / CRITERIO_REDUCCION) && heap->tam == TAM_INICIAL)
        return realloc_heap(heap, (size_t)((double)heap->tam * REDUCIR));
    return true;
}

/***************************
 * Primitivas
***************************/
heap_t *heap_crear(cmp_func_t cmp)
{
    heap_t *heap = malloc(sizeof(heap_t));
    if (!heap)
        return NULL;
    void **datos = malloc(sizeof(void *));
    if (!datos)
    {
        free(heap);
        return NULL;
    }
    heap->datos = datos;
    heap->cmp = cmp;
    heap->cant = 0;
    heap->tam = TAM_INICIAL;
    return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp)
{
    heap_t *heap = malloc(sizeof(heap_t));
    if (!heap)
        return NULL;
    void **datos = malloc(sizeof(void *));
    if (!datos)
    {
        free(heap);
        return NULL;
    }
    heap->datos = datos;
    size_t cant = 0;
    for (size_t i = 0; i < n; i++)
    {
        heap_encolar(heap, arreglo[i]);
        cant++;
    }
    heap->cmp = cmp;
    heap->cant = cant;
    heap->tam = TAM_INICIAL;
    return heap;
}

size_t heap_cantidad(const heap_t *heap)
{
    return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap)
{
    return !heap->cant;
}

void *heap_ver_max(const heap_t *heap)
{
    if (heap_esta_vacio(heap))
        return NULL;
    return heap->datos[0];
}

bool heap_encolar(heap_t *heap, void *elem)
{
    if (!elem)
        return NULL;
    if (!redimension(heap))
        return false;
    heap->datos[heap->cant] = elem;
    upHeap(heap, heap->cant);
    heap->cant++;
    return true;
}

void *heap_desencolar(heap_t *heap)
{
    if (heap_esta_vacio(heap))
        return NULL;
    void *max = heap_ver_max(heap);
    size_t i_final = heap->cant - 1;
    heap->datos[0] = heap->datos[i_final];
    heap->datos[i_final] = NULL;
    if (!redimension(heap))
        return false;
    heap->cant--;
    if (heap->cant == 0)
        return max;
    downHeap(heap, 0);
    return max;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp)
{
    return;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e))
{
    while (!heap_esta_vacio(heap))
    {
        void *dato = heap_desencolar(heap);
        if (destruir_elemento)
            destruir_elemento(dato);
    }
    free(heap->datos);
    free(heap);
}