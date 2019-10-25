#include "grep.h"
#include "cola.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR_READ 400

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    fprintf(stderr, "Cantidad de parametros erronea\n");
    return -1;
  }

  // for (int count = 1; count < argc; count++)
  //   printf("argv[%d] = %s\n", count, argv[count]);

  char *str_key = !argv[1] ? NULL : argv[1]; // 1 - palabra a buscar

  int n_lineas = atoi(argv[2]); // 2 - lineas
  // if (!isdigit(n_lineas))
  // {
  //   fprintf(stderr, "Tipo de parametro incorrecto\n");
  //   return -1;
  // }
  char *file = !argv[3] ? NULL : argv[3]; // 3 - archivo
  grep(str_key, n_lineas, file);
  return 0;
}

char *_copiar_string(const char *str)
{
  char *copia_clave = malloc(strlen(str) + 1);
  if (!copia_clave)
    return NULL;
  strcpy(copia_clave, str);
  return copia_clave;
}

void _print_lineas_cola(cola_t *cola)
{
  while (!cola_esta_vacia(cola))
  {
    char *linea = cola_desencolar(cola);
    printf("%s", linea);
    free(linea);
  }
}

bool grep(char *str_key, int n_lineas, char *file)
{
  FILE *fp = !file ? stdin : fopen(file, "r");
  if (!fp)
  {
    fprintf(stderr, "No se pudo leer el archivo indicado\n");
    return false;
  }

  char almacenamiento[MAX_CHAR_READ];
  cola_t *cola_lineas = cola_crear();
  int lineas_almacenadas = 0;
  bool encontro_substrings = false;

  while (fgets(almacenamiento, MAX_CHAR_READ, fp))
  {
    bool is_substring = strstr(almacenamiento, str_key);

    if (is_substring)
    {
      _print_lineas_cola(cola_lineas);
      printf("%s", almacenamiento);
      encontro_substrings = true;
      lineas_almacenadas = 0;
    }

    if (n_lineas > 0)
    {
      cola_encolar(cola_lineas, _copiar_string(almacenamiento)); // copiar para evitar invalid free
      lineas_almacenadas++;
    }

    if (lineas_almacenadas > n_lineas)
    {
      void *linea = cola_desencolar(cola_lineas);
      free(linea);
      lineas_almacenadas--;
    }
  }

  fclose(fp);
  cola_destruir(cola_lineas, free);

  return encontro_substrings;
}