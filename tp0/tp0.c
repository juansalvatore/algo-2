#include "tp0.h"
#include <stdio.h>
#include <stdbool.h>

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y)
{
  int previous_x = *x;
  *x = *y;
  *y = previous_x;
}

int maximo(int vector[], int n)
{
  if (n == 0)
  {
    return -1;
  }

  int max = vector[0];
  int max_index;
  for (int i = 0; i < n; i++)
  {
    if (vector[i] >= max)
    {
      max = vector[i];
      max_index = i;
    }
  }
  return max_index;
}

/* Devuelve un booleano dependiendo de si el valor 
 * existe en el vector o no.
 */
bool existe_en_vector(int valor, int vector[], int n)
{
  bool existe_en_vector = false;
  for (int i = 0; i < n; i++)
  {
    if (valor == vector[i])
    {
      existe_en_vector = true;
      break;
    }
  }
  return existe_en_vector;
}

/* Compara dos arreglos de longitud especificada.
 *
 * Devuelve -1 si el primer arreglo es menor que el segundo; 0 si son
 * iguales; o 1 si el primero es el mayor.
 *
 * Un arreglo es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
	int vec2[] = {4, 8, 15, 16, 23, 42}, vec2_ord[] = {4, 8, 15, 16, 23, 42};
	int vec3[] = {-38, -46, -65, -78}, vec3_ord[] = {-78, -65, -46, -38};
  0
 */
int comparar(int vector1[], int n1, int vector2[], int n2)
{
  for (int i = 0; i < n1; i++)
  {
    if (i + 1 > n2)
    {
      return 1;
    }
    if (vector1[i] == vector2[i])
    {
      continue;
    }
    if (vector1[i] > vector2[i])
    {
      return 1;
    }
    if (!existe_en_vector(vector1[i], vector2, n2) || vector1[i] < vector2[i])
    {
      return -1;
    }
  }

  if (n1 < n2)
  {
    return -1;
  }

  return 0;
}

void seleccion(int vector[], int n)
{
  int i = n - 1;
  while (i > 0)
  {
    int i_maximo = maximo(vector, i);
    swap(&vector[i], &vector[i_maximo]);
    i--;
  }
}
