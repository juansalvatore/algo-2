
#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdbool.h>


struct lista; // Definicion completa en lista.c
typedef struct lista lista_t;

// Iterador externo de listas
typedef struct lista_iter lista_iter_t;

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Inserta un elemento al comienzo de la lista, retorna false en caso de error.
// Pre: la lista fue creada.
// Post: se inserto un nuevo elemento al comienzo de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Inserta un elemento al final de la lista, retorna false en caso de error.
// Pre: la lista fue creada.
// Post: se inserto un nuevo elemento al final de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Se elimina el primer elemento de la lista. Retorna el elemento eliminado, en caso
// denestar vacía retorna NULL.
// Pre: la lista fue creada.
// Post: la lista tiene todos los elementos a excepción del primero.
void *lista_borrar_primero(lista_t *lista);

// Retorna el primer elemento de la lista, retorna NULL en caso de estar vacía.
// Pre: la lista fue creada.
// Post: retorna el primer elemento de la lista o NULL si esta vacía. 
// La lista permanece inmutada.
void *lista_ver_primero(const lista_t *lista);

// Retorna el ultimo elemento de la lista, retorna NULL en caso de estar vacía.
// Pre: la lista fue creada.
// Post: retorna el ultimo elemento de la lista o NULL si esta vacía. 
// La lista permanece inmutada.
void *lista_ver_ultimo(const lista_t *lista);

// Retorna la cantidad de elementos o el largo de la lista.
// Pre: la lista fue creada.
// Post: retorna el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la pila. Si recibe un parametro destruir_dato, ejecuta esa función para
// cada elemento de la lista.
// Pre: la lista fue creada.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

// Recorre la lista elemento a elemento y aplica la función visitar.
// Pre: la lista fue creada.
// Post: se ejecuto la funcion visitar para cada elemento.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

// Iterador externo
lista_iter_t *lista_iter_crear(lista_t *lista);

bool lista_iter_avanzar(lista_iter_t *iter);

void *lista_iter_ver_actual(const lista_iter_t *iter);

bool lista_iter_al_final(const lista_iter_t *iter);

void lista_iter_destruir(lista_iter_t *iter);

bool lista_iter_insertar(lista_iter_t *iter, void *dato);

void *lista_iter_borrar(lista_iter_t *iter);

#endif