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
struct heap {
    void **datos;
    size_t cant;
    size_t tam;
    cmp_func_t cmp;
};

/***************************
 * Funciones auxiliares
***************************/
void swap (void *x, void *y) {
    void *aux = x;
    x = y;
    y = aux;
}

int indice_hijo_izquierdo(size_t i) {
    return 2 * i + 1;
}

int indice_hijo_derecho(size_t i) {
    return 2 * i + 2;
}

int indice_padre(size_t i) {
    return (i-1)/2;
}

bool upHeap(heap_t *heap, size_t i) {
    void *elem_actual = heap->datos[i];
    int i_padre = indice_padre(heap->cant-1);
    if (heap->cmp(elem_actual, heap->datos[i_padre]) > 0) {
        void *aux = elem_actual;
        heap->datos[heap->cant-1] = heap->datos[i_padre];
        heap->datos[i_padre] = aux;
    } else {
        return true;
    }
    return upHeap(heap, i_padre);
}

void downHeap(heap_t *heap, size_t i) {
    void *elem_actual = heap->datos[i];
    int i_hijo_izq = hijo_izquierdo(i);
    int i_hijo_der = hijo_derecho(i);
    void *elem_hijo_izq;
    void *elem_hijo_der;
    if (i_hijo_izq < heap->cant)
        elem_hijo_izq = heap->datos[i_hijo_izq];
    if (i_hijo_der < heap->cant)
        elem_hijo_der = heap->datos[i_hijo_der];
}

void heapify() {

}

bool realloc_heap(heap_t* heap, size_t nueva_capacidad) {
    void* redimension = realloc(heap->datos, nueva_capacidad * sizeof(void*));
    if(redimension == NULL) return false;
    heap->datos = redimension;
    heap->tam = nueva_capacidad;
    return true;
}

bool redimension(heap_t* heap) {
    if (heap->cant == heap->tam) 
        return realloc_pila(heap, (heap->tam * EXPANDIR));

    if (heap->cant <= (heap->tam / CRITERIO_REDUCCION) && heap->tam == TAM_INICIAL)
        return realloc_pila(heap, (size_t)((double)heap->tam * REDUCIR));   
    return true;
}

/***************************
 * Primitivas
***************************/
heap_t *heap_crear(cmp_func_t cmp) {
    heap_t *heap = malloc(sizeof(heap_t));
    if (!heap) 
        return NULL;
    void **datos = malloc(sizeof(void*));
    if (!datos) {
        free(heap);
        return NULL;
    }
    heap->datos = datos;
    heap->cmp = cmp;
    heap->cant = 0;
    heap->tam = TAM_INICIAL;
    return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    heap_t *heap = malloc(sizeof(heap_t));
    if (!heap)
        return NULL;
    void **datos = malloc(sizeof(void*));
    if (!datos) {
        free(heap);
        return NULL;
    }
    heap->datos = datos;
    size_t cant = 0;
    for (size_t i = 0; i < n; i++) {
        heap_encolar(heap, arreglo[i]);
        cant++;
    }
    heap->cmp = cmp;
    heap->cant = cant;
    heap->tam = TAM_INICIAL;
    return heap;
}

size_t heap_cantidad(const heap_t *heap) {
    return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap) {
    return !!heap->cant;
}

void *heap_ver_max(const heap_t *heap) {
    if (heap_esta_vacio(heap)) 
        return NULL;
    return heap->datos[0];
}

bool heap_encolar(heap_t *heap, void *elem) {
    if (!redimension(heap)) return false;
    heap->datos[heap->cant] = elem;
    heap->cant++;
    return upHeap(heap, heap->cant-1);
}

void *heap_desencolar(heap_t *heap) {
    if (heap_esta_vacio(heap)) return NULL;
    void *max = heap_ver_max(heap);
    heap->datos[0] = heap->datos[heap->cant-1];
    heap->datos[heap->cant-1] = NULL;
    if (!redimension(heap)) return false;
    downHeap(heap, 0);
    return max;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
    return;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
    while (!heap_esta_vacio(heap)) {
        void *dato = heap_desencolar(heap);
        if (destruir_elemento)
            destruir_elemento(dato);
    }
    free(heap->datos);
    free(heap);
}