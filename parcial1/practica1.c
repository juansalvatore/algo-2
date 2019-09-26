#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
// 1. Implementar en C el TDA ComposicionFunciones que emula la composicion de funciones (i.e. f(g(h(x))).
// Se debe definir la estructura del TDA, y las siguientes primitivas:
// • composicion_t* composicion_crear( );
// • void composicion_destruir(composicion_t*);
// • bool composicion_agregar_funcion(composicion_t, double(f)(double));
// • double composicion_aplicar(composicion_t*, double);
// Considerar que primero se iran agregando las funciones como se leen, pero tener en cuenta el correcto orden de
// aplicacion. Por ejemplo: para emular f(g(x)), se debe hacer:
// composicion_agregar_funcion(composicion, f) → composicion_agregar_funcion(composicion, g) →
// composicion_aplicar(composicion, x)

typedef struct pila
{
} pila_t;

typedef struct composicion
{
  pila_t *funciones;
} composicion_t;

composicion_t *composicion_crear()
{
  composicion_t *composicion = malloc(sizeof(composicion_t));
  if (composicion == NULL)
    return NULL;
  composicion->funciones = Pila_Crear();
  if (composicion->funciones == NULL)
  {
    free(composicion->funciones);
    return NULL;
  }
  return composicion;
}

bool composicion_agregar_funcion(composicion_t *composicion, double f(double))
{
  return Pila_Apilar(composicion->funciones, f);
}

void composicion_destruir(composicion_t *composicion)
{
  Pila_Destruir(composicion->funciones);
  free(composicion);
}

double composicion_aplicar(composicion_t *composicion, double x)
{
  double resultado = x;
  while (!Pila_Esta_Vacia(composicion->funciones))
  {
    resultado = Pila_Desapilar(composicion->funciones)(resultado);
  }
  return resultado;
}