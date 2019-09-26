#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int toInt(void *num)
{
  return *(int *)num;
}

void destruir_dato(void *dato)
{
  free(dato);
}

void pruebas_generales()
{
  printf("\nINICIO DE PRUEBAS GENERALES  LISTA\n");
  lista_t *lista = lista_crear();

  printf("-> pruebas int\n");
  int n = 42;
  print_test("inserta int al comienzo", lista_insertar_primero(lista, &n));
  print_test("el numero es 42", *(int *)lista_ver_primero(lista) == n);
  print_test("largo == 1", lista_largo(lista) == 1);

  printf("-> pruebas string\n");
  char palabra[5] = "chau!";
  print_test("inserta un string", lista_insertar_ultimo(lista, palabra));
  print_test("largo == 2", lista_largo(lista) == 2);
  print_test("ultimo elemento == chau!", lista_ver_ultimo(lista) == palabra);
  print_test("el primero sigue siendo el numero 42", toInt(lista_ver_primero(lista)) == n);

  lista_destruir(lista, NULL);
}

void pruebas_generales_cantidad()
{
  printf("\nINICIO DE PRUEBAS DE VOLUMEN LISTA\n");
  lista_t *lista = lista_crear();

  int size = 1000;
  printf("-> prueba insertar %d elementos al comienzo\n", size);
  bool lista_inserta_ok = true;
  for (int i = 0; i < size && lista_inserta_ok; i++)
  {
    lista_inserta_ok = lista_insertar_primero(lista, &i);
  }
  print_test("se insertaron ok al principio", lista_inserta_ok == true);
  print_test("cantidad al final == 1000", lista_largo(lista) == size);

  lista_destruir(lista, NULL);

  printf("-> prueba insertar %d elementos al final\n", size);
  lista_t *lista2 = lista_crear();
  bool lista_inserta_ok2 = true;
  for (int i = 0; i < size && lista_inserta_ok2; i++)
  {
    lista_inserta_ok2 = lista_insertar_ultimo(lista2, &i);
  }
  print_test("se insertaron ok al final", lista_inserta_ok2 == true);
  print_test("cantidad al final == 1000", lista_largo(lista2) == size);
  lista_destruir(lista2, NULL);

  printf("-> prueba insertar %d elementos alocando memoria\n", size);
  lista_t *lista3 = lista_crear();
  bool lista_inserta_ok3 = true;
  for (int i = 0; i < size && lista_inserta_ok3; i++)
  {
    int *vector = malloc(20 * sizeof(int));
    lista_inserta_ok3 = lista_insertar_ultimo(lista3, vector);
  }
  print_test("se insertaron ok al final", lista_inserta_ok3 == true);
  print_test("cantidad al final == 1000", lista_largo(lista3) == size);
  printf("destruir datos con función propia\n");
  lista_destruir(lista3, destruir_dato);
}

bool _print_item(void *item, void *extra)
{
  int *cont = extra;
  cont++;
  printf("%s-", (char *)item);
  return true;
}

void pruebas_generales_iterador_interno()
{
  printf("\nINICIO DE PRUEBAS ITERADOR INTERNO LISTA\n");
  lista_t *lista = lista_crear();

  printf("itero con la lista vacía\n");
  lista_iterar(lista, _print_item, 0);

  char palabra1[4] = "hola";
  char palabra2[4] = "chau";
  print_test("insertar palabras", lista_insertar_primero(lista, palabra2) && lista_insertar_primero(lista, palabra1));
  int cont = 0;
  lista_iterar(lista, _print_item, &cont);
  printf("%d\n", cont);
  lista_destruir(lista, NULL);
}

void pruebas_lista_alumno()
{
  pruebas_generales();
  pruebas_generales_cantidad();
  pruebas_generales_iterador_interno();
}