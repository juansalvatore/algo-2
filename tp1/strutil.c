#include "strutil.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *substr(const char *str, size_t n)
{
  if (n > strlen(str))
  {
    char *cadena = malloc(sizeof(char) * (strlen(str) + 1));
    if (!cadena)
      return NULL;
    strcpy(cadena, str);
    return cadena;
  }

  char *nueva_cadena = malloc(sizeof(char) * (size_t)(n + 1));
  if (!nueva_cadena)
    return NULL;
  int i = 0;
  while (i < n)
  {
    nueva_cadena[i] = str[i];
    i++;
  }
  nueva_cadena[i] = '\0';
  return nueva_cadena;
}

int _count_splits(const char *str, char sep)
{
  int total_splits = 0;
  for (int i = 0; i < strlen(str); i++)
    if (str[i] == sep)
      total_splits++;
  total_splits++;
  return total_splits;
}

int _array_total_splits(char **strv, size_t *cantidad_chars)
{
  int total_splits = 0;
  while (strv[total_splits])
  {
    (*cantidad_chars) += strlen(strv[total_splits]);
    total_splits++;
  }
  return total_splits;
}

char **split(const char *str, char sep)
{
  int total_splits = _count_splits(str, sep);
  char **nueva_cadena = malloc(sizeof(char *) * (total_splits + 1));
  int split_start = 0;
  int nueva_cadena_i = 0;
  for (int i = 0; i <= strlen(str); i++)
    if (str[i] == sep || str[i] == '\0') // previene caso borde
    {
      // substr("ej,emplo" + 3, 5) == "emplo"
      nueva_cadena[nueva_cadena_i] = substr(str + split_start, i - split_start);
      split_start = i + 1; // salta separador
      nueva_cadena_i++;
    }
  nueva_cadena[total_splits] = NULL;
  return nueva_cadena;
}

char *join(char **strv, char sep)
{
  if (!strv[0])
  {
    char *empty_string = malloc(sizeof(char));
    empty_string[0] = '\0';
    return empty_string;
  }

  size_t cantidad_chars = 0;
  size_t total_splits = _array_total_splits(strv, &cantidad_chars);
  size_t new_string_len = cantidad_chars + total_splits;

  char *joined_string = malloc(sizeof(char) * new_string_len);
  if (!joined_string)
    return NULL;
  joined_string[0] = '\0';

  char _sep[1];
  _sep[0] = sep;

  size_t i_actual = 0;
  for (size_t i = 0; i < new_string_len; i++)
  {
    strcat(joined_string + i_actual, strv[i]);
    if (!strv[i + 1])
    {
      strcat(joined_string, "\0");
      return joined_string;
    }
    i_actual += strlen(strv[i]);
    strcat(joined_string, _sep);
  }
  return joined_string;
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
