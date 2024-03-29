#include "abb.h"
#include "pila.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct abb_nodo
{
  struct abb_nodo *izq;
  struct abb_nodo *der;
  char *clave;
  void *dato;
} abb_nodo_t;

struct abb
{
  abb_nodo_t *raiz;
  abb_comparar_clave_t cmp;
  abb_destruir_dato_t destruir_dato;
  size_t cantidad;
};

struct abb_iter
{
  pila_t *pila;
};

char *_copiar_string(const char *str)
{
  char *copia_clave = malloc(strlen(str) + 1);
  if (!copia_clave)
    return NULL;
  strcpy(copia_clave, str);
  return copia_clave;
}

abb_t *abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato)
{
  abb_t *abb = malloc(sizeof(abb_t));
  if (!abb)
    return NULL;
  abb->raiz = NULL;
  abb->cmp = cmp;
  abb->destruir_dato = destruir_dato;
  abb->cantidad = 0;
  return abb;
}

abb_nodo_t *_crear_nodo(const char *clave, void *dato)
{
  abb_nodo_t *abb_nodo = malloc(sizeof(abb_nodo_t));
  if (!abb_nodo)
    return NULL;
  abb_nodo->izq = NULL;
  abb_nodo->der = NULL;
  abb_nodo->clave = _copiar_string(clave);
  abb_nodo->dato = dato;
  return abb_nodo;
}

abb_nodo_t *_insertar_nodo(abb_t *arbol, const char *clave, void *dato, abb_nodo_t *nodo)
{
  if (!nodo)
  {
    arbol->cantidad++;
    return _crear_nodo(clave, dato);
  }

  int comp = arbol->cmp(nodo->clave, clave);
  if (!comp)
  {
    if (arbol->destruir_dato != NULL)
      arbol->destruir_dato(nodo->dato);

    nodo->dato = dato;
    return nodo;
  }
  else if (comp > 0)
    nodo->izq = _insertar_nodo(arbol, clave, dato, nodo->izq);
  else
    nodo->der = _insertar_nodo(arbol, clave, dato, nodo->der);
  return nodo;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato)
{
  if (!arbol)
    return false;
  if (!arbol->raiz)
  {
    arbol->raiz = _crear_nodo(clave, dato);
    arbol->cantidad++;
    return true;
  }
  abb_nodo_t *nodo = arbol->raiz;
  return !!_insertar_nodo(arbol, clave, dato, nodo);
}

abb_nodo_t *_abb_obtener(abb_nodo_t *nodo, abb_comparar_clave_t cmp, const char *clave)
{
  if (!nodo)
    return NULL;
  int comp = cmp(nodo->clave, clave);
  if (comp > 0)
    return _abb_obtener(nodo->izq, cmp, clave);
  else if (comp < 0)
    return _abb_obtener(nodo->der, cmp, clave);
  return nodo;
}

void *abb_obtener(const abb_t *arbol, const char *clave)
{
  if (!arbol)
    return NULL;
  abb_nodo_t *nodo = _abb_obtener(arbol->raiz, arbol->cmp, clave);
  if (!nodo)
    return NULL;
  return nodo->dato;
}

abb_nodo_t *_borrar_nodo(abb_nodo_t *nodo, abb_t *arbol, char *direccion)
{
  abb_nodo_t *nodo_actual = NULL;
  if (!strcmp(direccion, "izq"))
    nodo_actual = nodo->izq;
  else if (!strcmp(direccion, "der"))
    nodo_actual = nodo->der;
  else
    return NULL;
  free(nodo->clave);
  free(nodo);
  return nodo_actual;
}

abb_nodo_t *_abb_borrar(abb_nodo_t *nodo, abb_t *arbol, abb_comparar_clave_t cmp, const char *clave)
{
  if (!nodo)
    return NULL;
  int comp = cmp(nodo->clave, clave);
  if (!comp)
  { // Nodo encontrado
    if (nodo->izq && nodo->der)
    { // Si tiene hijo izquierdo y derecho
      abb_nodo_t *nodo_actual = nodo->izq;
      while (nodo_actual->der) // Busca al mas derecho de los izquierdos (clave mas grande de las mas chicas del nodo a borrar)
        nodo_actual = nodo_actual->der;
      free(nodo->clave);                                                  // Libera memoria clave
      nodo->dato = nodo_actual->dato;                                     // Intercambia el dato
      nodo->clave = _copiar_string(nodo_actual->clave);                   // Intercambia la clave
      nodo->izq = _abb_borrar(nodo->izq, arbol, cmp, nodo_actual->clave); // conecta nuevamente el sub arbol izquierdo (la derecha sigue fija)
    }
    else if (!nodo->izq)
      return _borrar_nodo(nodo, arbol, "der"); // Sin hijo izquierdo, devuelvo el sub arbol derecho
    else if (!nodo->der)
      return _borrar_nodo(nodo, arbol, "izq"); // Sin hijo derecho, devuelvo el sub arbol izquierdo
  }
  else if (comp < 0) // Avanzar a la izquierda
    nodo->izq = _abb_borrar(nodo->izq, arbol, cmp, clave);
  // Avanzar a la derecha
  nodo->der = _abb_borrar(nodo->der, arbol, cmp, clave);
  return nodo;
}

void *abb_borrar(abb_t *arbol, const char *clave)
{
  if (!arbol)
    return NULL;
  abb_nodo_t *nodo_borrado = _abb_obtener(arbol->raiz, arbol->cmp, clave);
  if (nodo_borrado == NULL)
    return NULL;
  void *dato_borrado = nodo_borrado->dato;
  arbol->raiz = _abb_borrar(arbol->raiz, arbol, arbol->cmp, clave);
  arbol->cantidad--;
  return dato_borrado;
}

bool abb_pertenece(const abb_t *arbol, const char *clave)
{
  if (!arbol)
    return false;
  return !!_abb_obtener(arbol->raiz, arbol->cmp, clave);
}

size_t abb_cantidad(abb_t *arbol)
{
  return arbol->cantidad;
}

void _abb_destruir(abb_nodo_t *nodo, abb_destruir_dato_t destruir_dato)
{
  if (!nodo)
    return;
  _abb_destruir(nodo->izq, destruir_dato);
  _abb_destruir(nodo->der, destruir_dato);
  if (destruir_dato)
    destruir_dato(nodo->dato);
  free(nodo->clave);
  free(nodo);
}

void abb_destruir(abb_t *arbol)
{
  _abb_destruir(arbol->raiz, arbol->destruir_dato);
  free(arbol);
}

// ITERADOR INTERNO

void _abb_in_order(abb_nodo_t *nodo, bool visitar(const char *, void *, void *), void *extra, bool *seguir)
{
  if (!nodo)
    return;
  _abb_in_order(nodo->izq, visitar, extra, seguir);
  if (visitar)
  {
    if (*seguir) 
    {
      *seguir = visitar(nodo->clave, nodo->dato, extra);
    }
  }
  if (*seguir) {
    _abb_in_order(nodo->der, visitar, extra, seguir);
  }
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra)
{
  if (!arbol || !arbol->raiz) return;
  bool seguir = true;
  _abb_in_order(arbol->raiz, visitar, extra, &seguir);
}

// ITERADOR EXTERNO
abb_iter_t *abb_iter_in_crear(const abb_t *arbol)
{
  abb_iter_t *iter = malloc(sizeof(abb_iter_t));
  if (!iter)
    return NULL;
  pila_t *pila = pila_crear();
  if (!pila)
    return NULL;
  if (arbol->raiz)
  {
    abb_nodo_t *nodo = arbol->raiz;
    while (nodo)
    {
      pila_apilar(pila, nodo);
      nodo = nodo->izq;
    }
  }
  iter->pila = pila;
  return iter;
}

bool abb_iter_in_al_final(const abb_iter_t *iter)
{
  return pila_esta_vacia(iter->pila);
}

bool abb_iter_in_avanzar(abb_iter_t *iter)
{
  if (abb_iter_in_al_final(iter))
    return false;
  abb_nodo_t *nodo = pila_desapilar(iter->pila);
  nodo = nodo->der;
  while (nodo)
  {
    pila_apilar(iter->pila, nodo);
    nodo = nodo->izq;
  }
  return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter)
{
  if (pila_esta_vacia(iter->pila))
    return NULL;
  abb_nodo_t *nodo = pila_ver_tope(iter->pila);
  return nodo->clave;
}

void abb_iter_in_destruir(abb_iter_t *iter)
{
  pila_destruir(iter->pila);
  free(iter);
}
