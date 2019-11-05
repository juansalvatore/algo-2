#include "heap.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM_INICIAL 20
// buscar como esta en la pila
#define TASA_REDIMENSION 0.5

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
    return true;
}

void *heap_desencolar(heap_t *heap) {
    return NULL;
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