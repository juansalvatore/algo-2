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

void _print_cola(void *dato)
{
  printf("%d\n", toInt(dato));
}

void pruebas_cola_general()
{
  printf("\nINICIO DE PRUEBAS GENERALES COLA\n");
  cola_t *cola = cola_crear();
  print_test("Cola inicializada", cola != NULL);
  int num = 42;
  print_test("Apila entero 42", cola_encolar(cola, &num));
  print_test("cola_ver_primero devuelve el primer elemento", toInt(cola_ver_primero(cola)) == num);
  print_test("Apila entero 42", cola_encolar(cola, &num));
  print_test("desencola entero 42", toInt(cola_desencolar(cola)) == num);
  print_test("desencola entero 42", toInt(cola_desencolar(cola)) == num);
  print_test("desencolar cola vacia devuelve NULL", cola_desencolar(cola) == NULL);
  print_test("Apila entero 42", cola_encolar(cola, &num));
  print_test("Apila entero 42", cola_encolar(cola, &num));
  print_test("Apila entero 42", cola_encolar(cola, &num));
  cola_destruir(cola, _print_cola);
  cola = cola_crear();
  print_test("Apila entero 42", cola_encolar(cola, &num));
  cola_destruir(cola, NULL);
}

void pruebas_cola_alumno()
{
  pruebas_cola_general();
}
