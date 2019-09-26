#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                       PRUEBAS UNITARIAS 
 * *****************************************************************/
int toInt(void *num)
{
  return *(int *)num;
}

void **cola_multiprimeros(cola_t *cola, size_t k)
{
  void **datos = malloc(sizeof(void *) * k);
  if (!datos)
    return NULL;
  cola_t *cola_aux = cola_crear();
  if (!cola_aux)
  {
    free(datos);
    return NULL;
  }
  for (size_t i = 0; i < k; i++)
  {
    void *desencolado = cola_desencolar(cola);
    if (desencolado)
      cola_encolar(cola_aux, desencolado);
    datos[i] = desencolado;
  }
  while (cola_esta_vacia(cola_aux))
    cola_encolar(cola, cola_desencolar(cola_aux));
  return datos;
}

void pruebas_cola_alumno()
{
  cola_t *cola = cola_crear();
  int valores[5] = {1, 2, 10, 4, 5};
  cola_encolar(cola, &valores[0]);
  cola_encolar(cola, &valores[1]);
  cola_encolar(cola, &valores[2]);
  cola_encolar(cola, &valores[3]);
  cola_encolar(cola, &valores[4]);

  void **arr = cola_multiprimeros(cola, 7);

  for (int j = 0; j < 7; j++)
  {
    int *dato = (int *)arr[j];
    if (dato)
      printf("\ndato: %d", *dato);
    else
      printf("\nnull pointer");
  }
}
