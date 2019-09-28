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

void imprimir_iter_externo(lista_t *lista)
{
  lista_iter_t *iter = lista_iter_crear(lista);
  int num_items = 0;

  while (!lista_iter_al_final(iter))
  {
    char *elemento = lista_iter_ver_actual(iter);
    printf("%d. %s\n", ++num_items, elemento);

    lista_iter_avanzar(iter);
  }
  printf("Tengo que comprar %d ítems\n", num_items);
  lista_iter_destruir(iter);
}

bool imprimir_un_item(void *elemento, void *extra)
{
  // Sabemos que ‘extra’ es un entero, por tanto le podemos hacer un cast.
  int *contador = extra;
  printf("%d. %s\n", ++(*contador), (char *)elemento);

  return true; // seguir iterando
}

bool free_imprimir_un_item(void *elemento, void *extra)
{
  int *contador = extra;
  printf("liberados: %d\n", ++(*contador));
  free(elemento);

  return true; // seguir iterando
}

void imprimir_iter_interno(lista_t *lista)
{
  int num_items = 0;
  lista_iterar(lista, imprimir_un_item, &num_items);
  printf("Tengo que comprar %d ítems\n", num_items);
}

void pruebas_generales()
{
  printf("\nINICIO DE PRUEBAS GENERALES  LISTA\n");
  lista_t *lista = lista_crear();
  print_test("borrar lista vacia", lista_borrar_primero(lista) == NULL);
  printf("-> pruebas int\n");
  int n = 42;
  print_test("inserta int al comienzo", lista_insertar_primero(lista, &n));
  print_test("el numero es 42", *(int *)lista_ver_primero(lista) == n);
  print_test("el numero es 42", *(int *)lista_ver_ultimo(lista) == n);
  print_test("largo == 1", lista_largo(lista) == 1);

  printf("-> pruebas string\n");
  char palabra[5] = "chau!";
  print_test("inserta un string", lista_insertar_ultimo(lista, palabra));
  print_test("largo == 2", lista_largo(lista) == 2);
  print_test("ultimo elemento == chau!", lista_ver_ultimo(lista) == palabra);
  print_test("el primero sigue siendo el numero 42", toInt(lista_ver_primero(lista)) == n);
  print_test("borrar lista primero lista", lista_borrar_primero(lista) == &n);

  lista_destruir(lista, NULL);
  lista_t *lista2 = lista_crear();
  print_test("inserta int al comienzo", lista_insertar_primero(lista2, &n));
  print_test("borrar lista primero lista", lista_borrar_primero(lista2) == &n);
  lista_destruir(lista2, NULL);
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
  imprimir_iter_interno(lista);

  print_test("se insertaron ok al final", lista_insertar_ultimo(lista, "leche") &&
                                              lista_insertar_ultimo(lista, "huevos") &&
                                              lista_insertar_ultimo(lista, "pan") &&
                                              lista_insertar_ultimo(lista, "mermelada"));
  imprimir_iter_interno(lista);
  lista_destruir(lista, NULL);

  lista_t *lista2 = lista_crear();
  int *vector = malloc(20 * sizeof(int));
  lista_insertar_primero(lista2, vector);
  int num_items = 0;
  lista_iterar(lista2, free_imprimir_un_item, &num_items);
  print_test("Numero de items eliminados == 1", num_items == 1);
  lista_destruir(lista2, NULL);
}

void pruebas_generales_iterador_externo()
{
  printf("\nINICIO DE PRUEBAS ITERADOR EXTERNO LISTA\n");
  lista_t *lista = lista_crear();

  printf("itero con la lista vacía\n");
  imprimir_iter_interno(lista);

  print_test("se insertaron ok al final", lista_insertar_ultimo(lista, "leche") &&
                                              lista_insertar_ultimo(lista, "huevos") &&
                                              lista_insertar_ultimo(lista, "pan") &&
                                              lista_insertar_ultimo(lista, "mermelada"));
  imprimir_iter_interno(lista);

  lista_iter_t *iter = lista_iter_crear(lista);
  char item1[4] = "hola";
  print_test("se insertaron ok al final", lista_iter_insertar(iter, item1));
  print_test("primero == hola", lista_ver_primero(lista) == item1);
  print_test("elemento actual == hola", lista_iter_ver_actual(iter) == item1);
  print_test("elemento borrado == hola", lista_iter_borrar(iter) == item1);
  print_test("primero != hola", lista_ver_primero(lista) != item1);
  lista_iter_t *iter2 = lista_iter_crear(lista);
  print_test("primero != hola", lista_iter_ver_actual(iter2));
  lista_iter_destruir(iter);
  lista_iter_destruir(iter2);
  lista_destruir(lista, NULL);
}

void prueba_iter_externo_hasta_final()
{
  lista_t *lista = lista_crear();

  int num = 1;
  print_test("se insertaron ok al final", lista_insertar_ultimo(lista, &num) &&
                                              lista_insertar_ultimo(lista, &num) &&
                                              lista_insertar_ultimo(lista, &num) &&
                                              lista_insertar_ultimo(lista, &num));
  lista_iter_t *iter = lista_iter_crear(lista);
  while (!lista_iter_al_final(iter))
  {
    printf("%d\n", toInt(lista_iter_ver_actual(iter)));
    lista_iter_avanzar(iter);
  }

  print_test("Ver actual == NULL", lista_iter_ver_actual(iter) == NULL);
  lista_iter_destruir(iter);
  lista_destruir(lista, NULL);
}

void pruebas_lista_alumno()
{
  pruebas_generales();
  pruebas_generales_cantidad();
  pruebas_generales_iterador_interno();
  pruebas_generales_iterador_externo();
  prueba_iter_externo_hasta_final();
}