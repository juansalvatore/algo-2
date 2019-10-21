#include "strutil.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *substr(const char *str, size_t n)
{
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

size_t _count_splits(const char *str, char sep)
{
  size_t total_splits = 0;
  for (int i = 0; i < strlen(str); i++)
    if (str[i] == sep)
      total_splits++;
  total_splits++;
  return total_splits;
}

size_t _array_total_splits(char **strv, int *cantidad_chars)
{
  size_t total_splits = 0;
  while(strv[total_splits]) 
  {
    (*cantidad_chars) += strlen(strv[total_splits]);
    total_splits++;
  }
  (*cantidad_chars)++;
  return total_splits;
}

char **split(const char *str, char sep)
{
  size_t total_splits = _count_splits(str, sep);
  char **nueva_cadena = malloc(sizeof(char *) * (total_splits + 1));
  int split_start = 0;
  int nueva_cadena_i = 0;
  for (int i = 0; i <= strlen(str); i++)
    if (str[i] == sep || str[i] == '\0') // \0 previene caso borde
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
  int cantidad_chars = 0;
  size_t total_splits = _array_total_splits(strv, &cantidad_chars);
  int new_string_len = cantidad_chars + total_splits;

  if(total_splits == 0 || (cantidad_chars == 0 && total_splits == 0))
    return "";
  if(total_splits == 1)
    return strv[0];

  char *joined_string = malloc(sizeof(char) * new_string_len);
  if(!joined_string)
    return NULL;

  char sep_casteado[2];
	
	sep_casteado[0] = sep;
	sep_casteado[1] = '\0';

  strcpy(joined_string, strv[0]);
  for(int i = 1; i < total_splits; i++)
  {
    strcat(joined_string, strv[i]);
    strcat(joined_string, sep_casteado);
  }
  joined_string[new_string_len - 1] = "\0";
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
