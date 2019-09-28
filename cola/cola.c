#include "cola.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct nodo
{
  void *dato;
  struct nodo *proximo;
} nodo_t;

struct cola
{
  nodo_t *primero;
  nodo_t *ultimo;
};

cola_t *cola_crear(void)
{
  cola_t *cola = malloc(sizeof(cola_t));
  if (cola == NULL)
    return NULL;
  cola->primero = NULL;
  cola->ultimo = NULL;
  return cola;
}

bool cola_esta_vacia(const cola_t *cola)
{
  return cola->primero == NULL;
}

nodo_t *_crear_nodo(void *valor)
{
  nodo_t *nodo = malloc(sizeof(nodo_t));
  if (nodo == NULL)
    return NULL;
  nodo->dato = valor;
  nodo->proximo = NULL;
  return nodo;
}

bool cola_encolar(cola_t *cola, void *valor)
{
  nodo_t *nuevo_nodo = _crear_nodo(valor);
  if (nuevo_nodo == NULL)
    return false;

  if (!cola_esta_vacia(cola))
    cola->ultimo->proximo = nuevo_nodo;
  else
    cola->primero = nuevo_nodo;
  cola->ultimo = nuevo_nodo;
  return true;
}

void *cola_ver_primero(const cola_t *cola)
{
  return !cola_esta_vacia(cola) ? cola->primero->dato : NULL;
}

void *cola_desencolar(cola_t *cola)
{
  if (cola_esta_vacia(cola))
    return NULL;
  void *dato = cola->primero->dato;
  nodo_t *nodo = cola->primero;
  cola->primero = cola->primero->proximo;
  if (!cola->primero)
    cola->ultimo = NULL;
  free(nodo);
  return dato;
}

void cola_destruir(cola_t *cola, void destruir_dato(void *))
{
  while (!cola_esta_vacia(cola))
  {
    void *dato_nodo_act = cola_desencolar(cola);
    if (destruir_dato != NULL)
      destruir_dato(dato_nodo_act);
  }
  free(cola);
}