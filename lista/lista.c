#include "lista.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct nodo
{
  void *dato;
  struct nodo *proximo;
} nodo_t;

struct lista
{
  nodo_t *primero;
  nodo_t *ultimo;
  size_t largo;
};

/*  
 * LISTA 
 */
lista_t *lista_crear(void)
{
  lista_t *lista = malloc(sizeof(lista_t));
  if (!lista)
    return NULL;
  lista->primero = NULL;
  lista->ultimo = NULL;
  lista->largo = 0;
  return lista;
}

bool lista_esta_vacia(const lista_t *lista)
{
  return lista->largo == 0;
}

// función auxiliar para crear nodos
nodo_t *_crear_nodo(void *dato, void *proximo)
{
  nodo_t *nodo = malloc(sizeof(nodo_t));
  if (!nodo)
    return NULL;
  nodo->dato = dato;
  nodo->proximo = proximo;
  return nodo;
}

bool lista_insertar_primero(lista_t *lista, void *dato)
{
  nodo_t *nuevo_nodo = _crear_nodo(dato, lista->primero);
  if (!nuevo_nodo)
    return false;
  if (lista_esta_vacia(lista))
  {
    lista->ultimo = nuevo_nodo;
    lista->ultimo->proximo = NULL;
  }
  lista->primero = nuevo_nodo;
  lista->largo++;
  return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato)
{
  nodo_t *nuevo_nodo = _crear_nodo(dato, NULL);
  if (!nuevo_nodo)
    return false;
  if (lista_esta_vacia(lista))
    lista->primero = nuevo_nodo;
  else
    lista->ultimo->proximo = nuevo_nodo;
  lista->ultimo = nuevo_nodo;
  lista->largo++;
  return true;
}

void *lista_ver_primero(const lista_t *lista)
{
  return lista_esta_vacia(lista) ? NULL : lista->primero->dato;
}

void *lista_borrar_primero(lista_t *lista)
{
  if (lista_esta_vacia(lista))
    return NULL;
  nodo_t *nodo_eliminado = lista->primero;
  void *dato_nodo_eliminado = lista_ver_primero(lista);
  lista->primero = lista->primero->proximo;
  free(nodo_eliminado);
  lista->largo--;
  return dato_nodo_eliminado;
}

void *lista_ver_ultimo(const lista_t *lista)
{
  return lista_esta_vacia(lista) ? NULL : lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista)
{
  return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *))
{
  nodo_t *nodo_actual = lista->primero;
  while (nodo_actual)
  {
    nodo_t *nodo_proximo = nodo_actual->proximo;
    if (destruir_dato)
      destruir_dato(nodo_actual->dato);
    free(nodo_actual);
    nodo_actual = nodo_proximo;
  }
  free(lista);
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra)
{
  nodo_t *nodo_actual = lista->primero;
  bool visitar_return = true;
  while (nodo_actual && visitar_return)
  {
    if (visitar)
      visitar_return = visitar(nodo_actual->dato, extra);
    nodo_actual = nodo_actual->proximo;
  }
}

/*  
 *  ITERADOR EXTERNO 
 */
struct lista_iter
{
  nodo_t *anterior;
  nodo_t *actual;
  lista_t *lista;
};

lista_iter_t *lista_iter_crear(lista_t *lista)
{
  lista_iter_t *iter = malloc(sizeof(lista_iter_t));
  if (!iter)
    return NULL;
  iter->anterior = NULL;
  iter->actual = lista->primero;
  iter->lista = lista;
  return iter;
}

void *lista_iter_ver_actual(const lista_iter_t *iter)
{
  return lista_iter_al_final(iter) ? NULL : iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter)
{
  return iter->actual == NULL;
}

bool lista_iter_avanzar(lista_iter_t *iter)
{
  if (lista_iter_al_final(iter) || lista_esta_vacia(iter->lista))
    return false;
  iter->anterior = iter->actual;
  iter->actual = iter->actual->proximo;
  return true;
}

void lista_iter_destruir(lista_iter_t *iter)
{
  free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato)
{
  nodo_t *nuevo_nodo = _crear_nodo(dato, iter->actual);
  if (!nuevo_nodo)
    return false;

  if (iter->anterior)
    iter->anterior->proximo = nuevo_nodo;
  if (iter->anterior == iter->lista->ultimo)
    iter->lista->ultimo = nuevo_nodo;
  if (iter->actual == iter->lista->primero)
    iter->lista->primero = nuevo_nodo;

  iter->actual = nuevo_nodo;
  iter->lista->largo++;
  return true;
}

void *lista_iter_borrar(lista_iter_t *iter)
{
  if (lista_iter_al_final(iter) || lista_esta_vacia(iter->lista))
    return NULL;
  nodo_t *nodo_eliminado = iter->actual;
  void *dato_nodo_eliminado = iter->actual->dato;
  iter->actual = iter->actual->proximo;

  if (iter->anterior)
    iter->anterior->proximo = iter->actual;
  if (nodo_eliminado == iter->lista->primero)
    iter->lista->primero = iter->actual;
  if (nodo_eliminado == iter->lista->ultimo)
    iter->lista->ultimo = iter->anterior;

  free(nodo_eliminado);
  iter->lista->largo--;
  return dato_nodo_eliminado;
}