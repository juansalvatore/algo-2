#include "tp0.h"
#include <stdio.h>
#include <stdbool.h>

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 *         Alumno: Juan Salvatore                                  *
 *         Padrón: 103746                                          *
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
    return -1;

  int max = vector[0];
  int max_index = -1;
  for (int i = 0; i < n; i++)
    if (vector[i] >= max)
    {
      max = vector[i];
      max_index = i;
    }
  return max_index;
}

int comparar_numeros(int a, int b)
{
  if (a < b)
    return -1;
  else if (a > b)
    return 1;
  else
    return 0;
}

int menor(int a, int b)
{
  return a < b ? a : b;
}

int comparar(int vector1[], int n1, int vector2[], int n2)
{
  for (int i = 0; i < menor(n1, n2); i++)
    if (vector1[i] != vector2[i])
      return comparar_numeros(vector1[i], vector2[i]);
  return comparar_numeros(n1, n2);
}

void seleccion(int vector[], int n)
{
  int i = n - 1;
  while (i > 0)
  {
    int max_index = maximo(vector, i);
    if (vector[max_index] > vector[i])
      swap(&vector[i], &vector[max_index]);
    i--;
  }
}
