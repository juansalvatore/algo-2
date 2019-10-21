#include "strutil.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

bool cadenas_ok(char **cadena1, char **cadena2, int largo)
{
  bool ok = true;
  for (int i = 0; i < largo; i++)
    ok = strcmp(cadena1[i], cadena2[i]) == 0 ? true : false;
  return ok;
}

// char **array_cadena_crear(size_t tam)
// {
//   char **array = malloc(tam * sizeof(char *));
//   if (array == NULL)
//     return NULL;
//   return array;
// }

// void test_split()
// {

//   printf("###### TEST SPLIT ######\n");

//   char **cadena_vacia = array_cadena_crear(1);
//   cadena_vacia[0] = "";
//   char **spliteado = split("", ',');

//   print_test("Split de cadena vacia", comparar_array_cadenas(spliteado, 1, cadena_vacia, 1));

//   free(cadena_vacia);
//   free_strv(spliteado);

//   char **cadena_sin_coma = array_cadena_crear(1);
//   cadena_sin_coma[0] = "Perro";
//   spliteado = split("Perro", ',');

//   print_test("Split sin separador", comparar_array_cadenas(spliteado, 1, cadena_sin_coma, 1));

//   free(cadena_sin_coma);
//   free_strv(spliteado);

//   char **cadena_tres = array_cadena_crear(4);
//   cadena_tres[0] = "Perro";
//   cadena_tres[1] = "";
//   cadena_tres[2] = "Gato";
//   spliteado = split("Perro,,Gato", ',');

//   print_test("Split con vacio", comparar_array_cadenas(spliteado, 3, cadena_tres, 3));

//   free(cadena_tres);
//   free_strv(spliteado);
// }

// void test_join()
// {

//   printf("###### TEST JOIN ######\n");

//   char **cadena_tres = array_cadena_crear(4);
//   cadena_tres[0] = "Auto";
//   cadena_tres[1] = "Barco";
//   cadena_tres[2] = "Caracol";
//   cadena_tres[3] = NULL;

//   char *joineado = join(cadena_tres, ',');
//   char *resultado = "Auto,Barco,Caracol";
//   print_test("Join de tres elementos", strcmp(joineado, resultado) == 0);
//   //printf("%s", joineado);

//   free(cadena_tres);
//   free(joineado);

//   char **cadena_uno = array_cadena_crear(2);
//   cadena_uno[0] = "Caracol";
//   cadena_uno[1] = NULL;

//   joineado = join(cadena_uno, ',');

//   resultado = "Caracol";
//   print_test("Join de un elemento", strcmp(joineado, resultado) == 0);

//   free(cadena_uno);
//   free(joineado);

//   char **cadena_vacios = array_cadena_crear(3);
//   cadena_vacios[0] = "";
//   cadena_vacios[1] = "";
//   cadena_vacios[2] = NULL;

//   joineado = join(cadena_vacios, ',');

//   resultado = ",";
//   print_test("Join de vacios", strcmp(joineado, resultado) == 0);

//   free(cadena_vacios);
//   free(joineado);

//   char **cadena_nula = array_cadena_crear(1);
//   cadena_nula[0] = NULL;

//   joineado = join(cadena_nula, ',');

//   print_test("Join de NULL", strcmp(joineado, "") == 0);

//   free(cadena_nula);
//   free(joineado);
// }

void test_split()
{
  printf("\nINICIO DE PRUEBAS SPLIT\n");

  printf("-->caso borde ''\n");
  char *substring = substr("hello", 3);
  print_test("substring == hel", strcmp(substring, "hel") == 0);

  char **array = malloc(2 * sizeof(char *));
  if (array == NULL)
    return NULL;
  array[0] = "";
  array[0] = NULL;

  char **splitted = split("", ',');
  print_test("split vacio == ''", strcmp(splitted[0], "") == 0);

  printf("-->caso estandard 'hola como estas'\n");
  char **resultado_esperado = malloc(4 * sizeof(char *));
  resultado_esperado[0] = "hola";
  resultado_esperado[1] = "como";
  resultado_esperado[2] = "estas";
  resultado_esperado[3] = NULL;
  char **splitted2 = split("hola como estas", ' ');

  bool ok = true;
  for (int i = 0; i < 3; i++)
  {
    ok = strcmp(splitted2[i], resultado_esperado[i]) == 0 ? true : false;
  }
  print_test("split 'hola como estas' == [hola, como, estas]", ok);

  printf("-->caso borde ','\n");
  char **resultado_esperado2 = malloc(3 * sizeof(char *));
  if (resultado_esperado2 == NULL)
    return NULL;
  resultado_esperado2[0] = "";
  resultado_esperado2[1] = "";
  resultado_esperado2[2] = NULL;

  char **splitted3 = split(",", ',');
  
  print_test("split ',' == ['', '']", cadenas_ok(splitted3, resultado_esperado2, 2));

  printf("-->caso borde 'abc,,def'\n");
  char **resultado_esperado3 = malloc(4 * sizeof(char *));
  if (resultado_esperado3 == NULL)
    return NULL;
  resultado_esperado3[0] = "abc";
  resultado_esperado3[1] = "";
  resultado_esperado3[2] = "def";
  resultado_esperado3[3] = NULL;

  char **splitted4 = split("abc,,def", ',');
  
  print_test("split ',' == ['abc', '', 'def']", cadenas_ok(splitted4, resultado_esperado3, 3));

  printf("-->caso borde 'abc,def,'\n");
  char **resultado_esperado4 = malloc(4 * sizeof(char *));
  if (resultado_esperado4 == NULL)
    return NULL;
  resultado_esperado4[0] = "abc";
  resultado_esperado4[1] = "def";
  resultado_esperado4[2] = "";
  resultado_esperado4[3] = NULL;

  char **splitted5 = split("abc,def,", ',');
  
  print_test("split ',' == ['abc', 'def', '']", cadenas_ok(splitted5, resultado_esperado4, 3));

  printf("-->caso borde ',abc,def'\n");
  char **resultado_esperado5 = malloc(4 * sizeof(char *));
  if (resultado_esperado5 == NULL)
    return NULL;
  resultado_esperado5[0] = "";
  resultado_esperado5[1] = "abc";
  resultado_esperado5[2] = "def";
  resultado_esperado5[3] = NULL;

  char **splitted6 = split(",abc,def", ',');
  
  print_test("split ',' == ['', 'abc', 'def']", cadenas_ok(splitted6, resultado_esperado5, 3));


  printf("-->caso borde 'abc'\n");
  char **resultado_esperado6 = malloc(2 * sizeof(char *));
  if (resultado_esperado6 == NULL)
    return NULL;
  resultado_esperado6[0] = "abc";
  resultado_esperado6[1] = NULL;

  char **splitted7 = split("abc", '\0');
  
  print_test("split '\\0' == ['abc']", cadenas_ok(splitted7, resultado_esperado6, 1));

  free_strv(splitted);
  free_strv(splitted2);
  free_strv(splitted3);
  free_strv(splitted4);
  free_strv(splitted5);
  free_strv(splitted6);
  free_strv(splitted7);
  free(array);
  free(substring);
  free(resultado_esperado);
  free(resultado_esperado2);
  free(resultado_esperado3);
  free(resultado_esperado4);
  free(resultado_esperado5);
  free(resultado_esperado6);
}

void test_join() {
  char **arr = malloc(4 * sizeof(char *));
  if (arr == NULL)
    return NULL;
  arr[0] = "";
  arr[1] = "abc";
  arr[2] = "def";
  arr[3] = NULL;
  char* new_string = join(arr, ',');
  printf("\n\n%s\n", new_string);
}

void pruebas_alumno(void)
{
  test_split();
  test_join();
}