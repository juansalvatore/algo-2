#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparar_numeros(const char *str1, const char *str2)
{

  if (atoi(str1) > atoi(str2))
    return -1;
  else if (atoi(str1) < atoi(str2))
    return 1;
  else
    return 0;
}

void test_crear()
{

  abb_t *arbol = abb_crear(strcmp, NULL);

  char *clave_1 = "14";
  char *dato_1 = "Perro";

  char *clave_2 = "9";
  char *dato_2 = "Gato";

  char *clave_3 = "1";
  char *dato_3 = "Jirafa";

  print_test("Obtener es NULL", abb_obtener(arbol, clave_1) == NULL);
  print_test("Borrar es NULL", abb_borrar(arbol, clave_1) == NULL);

  print_test("Guardar elemento 1", abb_guardar(arbol, clave_1, dato_1));
  print_test("Obtener elemento 1", abb_obtener(arbol, clave_1) == dato_1);
  print_test("Cantidad es 1", abb_cantidad(arbol) == 1);

  print_test("Guardar elemento 2", abb_guardar(arbol, clave_2, dato_2));
  print_test("Obtener elemento 2", abb_obtener(arbol, clave_2) == dato_2);
  print_test("Cantidad es 2", abb_cantidad(arbol) == 2);

  print_test("Guardar elemento 3", abb_guardar(arbol, clave_3, dato_3));
  print_test("Obtener elemento 3", abb_obtener(arbol, clave_3) == dato_3);
  print_test("Cantidad es 3", abb_cantidad(arbol) == 3);

  print_test("Pertenece 1", abb_pertenece(arbol, clave_1));
  print_test("Pertenece 2", abb_pertenece(arbol, clave_2));
  print_test("Pertenece 3", abb_pertenece(arbol, clave_3));

  printf("Inorder: \n");
  abb_in_order(arbol, NULL, NULL);

  print_test("Borrar 1 (raiz)", abb_borrar(arbol, clave_1) == dato_1);
  print_test("Cantidad es 2", abb_cantidad(arbol) == 2);

  printf("Inorder: \n");
  abb_in_order(arbol, NULL, NULL);

  print_test("Obtener elemento 2", abb_obtener(arbol, clave_2) == dato_2);

  print_test("Borrar 2", abb_borrar(arbol, clave_2) == dato_2);
  print_test("Cantidad es 1", abb_cantidad(arbol) == 1);

  printf("Inorder: \n");
  abb_in_order(arbol, NULL, NULL);

  print_test("Borrar 3", abb_borrar(arbol, clave_3) == dato_3);
  print_test("Cantidad es 0", abb_cantidad(arbol) == 0);

  abb_destruir(arbol);
}

void test_reemplazar()
{

  char *claves[] = {"1", "2", "3", "4", "5", "6", "7", NULL};
  char *valores[] = {"1", "2", "3", "4", "5", "6", "7", NULL};

  abb_t *arbol = abb_crear(comparar_numeros, NULL);

  for (int i = 0; i < 7; i++)
  {
    abb_guardar(arbol, claves[i], valores[i]);
  }

  abb_in_order(arbol, NULL, NULL);

  abb_destruir(arbol);
}

void test_iter_externo()
{

  char *claves[] = {"1", "2", "3", "4", "5", "6", "7", NULL};
  char *valores[] = {"1", "2", "3", "4", "5", "6", "7", NULL};

  abb_t *arbol = abb_crear(comparar_numeros, NULL);

  for (int i = 0; i < 7; i++)
  {
    abb_guardar(arbol, claves[i], valores[i]);
  }

  abb_iter_t *iter = abb_iter_in_crear(arbol);

  while (!abb_iter_in_al_final(iter))
  {
    printf("%s\n", abb_iter_in_ver_actual(iter));
    abb_iter_in_avanzar(iter);
  }

  abb_iter_in_destruir(iter);

  abb_destruir(arbol);
}

static void prueba_abb_insertar()
{
  abb_t *abb = abb_crear(strcmp, NULL);

  char *clave1 = "3", *valor1 = "guau";
  char *clave2 = "4", *valor2 = "miau";
  char *clave3 = "2", *valor3 = "mu";

  print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
  print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
  print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
  print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
  print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
  print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
  print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

  /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
  print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
  print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
  print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
  print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
  print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

  print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
  print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
  print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
  print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
  print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

  abb_destruir(abb);
}

static void prueba_abb_reemplazar()
{
  abb_t *abb = abb_crear(comparar_numeros, NULL);

  char *clave1 = "1", *valor1a = "3", *valor1b = "5";
  char *clave2 = "2", *valor2a = "4", *valor2b = "6";

  /* Inserta 2 valores y luego los reemplaza */
  print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
  print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
  print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
  print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
  print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

  print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
  print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
  print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
  print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
  print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

  abb_destruir(abb);
}

void pruebas_abb_alumno()
{
  test_crear();
  test_reemplazar();
  test_iter_externo();
  prueba_abb_insertar();
  prueba_abb_reemplazar();
}