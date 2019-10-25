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

void test_split()
{
  printf("\nINICIO DE PRUEBAS SPLIT\n");

  printf("-->caso borde ''\n");
  char *substring = substr("hello", 3);
  print_test("substring == hel", strcmp(substring, "hel") == 0);

  char **array = malloc(2 * sizeof(char *));

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

  resultado_esperado2[0] = "";
  resultado_esperado2[1] = "";
  resultado_esperado2[2] = NULL;

  char **splitted3 = split(",", ',');

  print_test("split ',' == ['', '']", cadenas_ok(splitted3, resultado_esperado2, 2));

  printf("-->caso borde 'abc,,def'\n");
  char **resultado_esperado3 = malloc(4 * sizeof(char *));

  resultado_esperado3[0] = "abc";
  resultado_esperado3[1] = "";
  resultado_esperado3[2] = "def";
  resultado_esperado3[3] = NULL;

  char **splitted4 = split("abc,,def", ',');

  print_test("split ',' == ['abc', '', 'def']", cadenas_ok(splitted4, resultado_esperado3, 3));

  printf("-->caso borde 'abc,def,'\n");
  char **resultado_esperado4 = malloc(4 * sizeof(char *));

  resultado_esperado4[0] = "abc";
  resultado_esperado4[1] = "def";
  resultado_esperado4[2] = "";
  resultado_esperado4[3] = NULL;

  char **splitted5 = split("abc,def,", ',');

  print_test("split ',' == ['abc', 'def', '']", cadenas_ok(splitted5, resultado_esperado4, 3));

  printf("-->caso borde ',abc,def'\n");
  char **resultado_esperado5 = malloc(4 * sizeof(char *));
  resultado_esperado5[0] = "";
  resultado_esperado5[1] = "abc";
  resultado_esperado5[2] = "def";
  resultado_esperado5[3] = NULL;

  char **splitted6 = split(",abc,def", ',');

  print_test("split ',' == ['', 'abc', 'def']", cadenas_ok(splitted6, resultado_esperado5, 3));

  printf("-->caso borde 'abc'\n");
  char **resultado_esperado6 = malloc(2 * sizeof(char *));
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

void test_join()
{
  printf("-->caso borde ['abc']\n");
  char **arr = malloc(2 * sizeof(char *));
  arr[0] = "abc";
  arr[1] = NULL;
  char *new_string = join(arr, '\0');
  printf("\n%s\n", new_string);
  free(arr);
  free(new_string);

  printf("-->caso ['abc', 'def']\n");
  char **arr2 = malloc(3 * sizeof(char *));
  arr2[0] = "abc";
  arr2[1] = "def";
  arr2[2] = NULL;
  char *new_string2 = join(arr2, ',');
  printf("\n%s\n", new_string2);
  free(arr2);
  free(new_string2);

  printf("-->caso ['']\n");
  char **arr3 = malloc(2 * sizeof(char *));
  arr3[0] = "";
  arr3[1] = NULL;
  char *new_string3 = join(arr3, ',');
  printf("\n%s\n", new_string3);
  free(arr3);
  free(new_string3);

  printf("-->caso []\n");
  char **arr4 = malloc(1 * sizeof(char *));
  arr4[0] = NULL;
  char *new_string4 = join(arr4, ',');
  printf("\n%s\n", new_string4);
  free(arr4);
  free(new_string4);

  printf("-->caso ["",""]\n");
  char **arr5 = malloc(3 * sizeof(char *));
  arr5[0] = "";
  arr5[1] = "";
  arr5[2] = NULL;
  char *new_string5 = join(arr5, ',');
  printf("\n%s\n", new_string5);
  free(arr5);
  free(new_string5);

  printf("-->caso ["",""]\n");
  char **arr6 = malloc(10 * sizeof(char *));
  arr6[0] = "a";
  arr6[1] = "b";
  arr6[2] = "c";
  arr6[3] = "d";
  arr6[4] = "e";
  arr6[5] = "f";
  arr6[6] = "g";
  arr6[7] = "h";
  arr6[8] = "i";
  arr6[9] = NULL;
  char *new_string6 = join(arr6, '\0');
  printf("\n%s\n", new_string6);
  free(arr6);
  free(new_string6);
}

void pruebas_alumno(void)
{
  test_split();
  test_join();
}