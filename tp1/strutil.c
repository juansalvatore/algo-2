#include "strutil.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *substr(const char *str, size_t n)
{
  char *nueva_cadena = malloc(sizeof(char) * (n + 1));
  if (!nueva_cadena)
    return NULL;
  for (int i = 0; i < n; i++)
    nueva_cadena[i] = str[i];
  return strcat(nueva_cadena, '\0');
}

char **split(const char *str, char sep)
{
  int i = 0;
  int total_splits = 0;
  while (str[i] != '\0')
    if (str[i] == sep)
      total_splits++;
  total_splits++; // teniendo en cuenta el '\0'

  char **nueva_cadena = malloc(sizeof(char *) * (total_splits + 1));
  i = 0;
  int split_start = 0;
  int nueva_cadena_i = 0;
  while (str[i] != '\0')
    if (str[i] == sep)
    {
      nueva_cadena[nueva_cadena_i] = substr(str + split_start, i - split_start);
      split_start = i + 1;
      nueva_cadena_i++;
    }
  nueva_cadena[total_splits] = NULL;
  return nueva_cadena;
}

char *join(char **strv, char sep)
{
  char *joined_string;
  int i = 0;
  while (strv[i]) // ya que esperamos que tenga NULL al final
  {
  }
}

void free_strv(char *strv[])
{
  int i = 0;
  while (strv[i])
  {
    free(strv[i]);
    i++;
  }
  free(strv);
}
