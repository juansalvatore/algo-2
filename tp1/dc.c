#include "dc.h"
#include "pila.h"
#include "strutil.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_READ 400
#define NaN "__NaN__"
char *OPERACIONES_1[] = {"sqrt"};
char *OPERACIONES_2[] = {"+", "-", "*", "/", "^", "log"};
char *OPERACIONES_3[] = {"?"};
enum
{
  UN_OPERANDO,
  DOS_OPERANDOS,
  TRES_OPERANDOS
};

bool is_number(char *str)
{
  if (atoi(str) == 0 && str[0] != '0')
    return false;
  return true;
}

char *_copiar_string(const char *str)
{
  char *copia_clave = malloc(strlen(str) + 1);
  if (!copia_clave)
    return NULL;
  strcpy(copia_clave, str);
  return copia_clave;
}

int _log(int n, int b)
{
  if (n < 0)
    return -1;
  if (n == b)
    return 1;
  if (n == 1 || n < b)
    return 0;
  return 1 + _log(n / b, b);
}

int potencia(int n, int repeticiones)
{
  if (repeticiones == 0)
    return 1;
  int x = potencia(n, repeticiones / 2);
  if (repeticiones % 2 == 0)
    return x * x;
  return n * x * x;
}

int _sqrt(int n)
{
  int inicio, fin, medio;
  inicio = 1;
  fin = n;
  while (inicio <= fin)
  {
    medio = (inicio + fin) / 2;
    if (medio * medio == n)
      return medio;
    if (medio * medio > n)
      fin = medio - 1;
    else
      inicio = medio + 1;
  }
  return fin;
}

bool desapilar_cantidad_necesaria(int *n1, int *n2, int *n3, int *n_operandos, char *operador, pila_t *pila_int)
{
  for (int j = 0; j < sizeof OPERACIONES_1 / sizeof OPERACIONES_1[0]; j++)
    if (!strcmp(operador, OPERACIONES_1[j]))
    {
      *n1 = atoi(pila_desapilar(pila_int));
      *n_operandos = UN_OPERANDO;
      return true;
    }
  for (int j = 0; j < sizeof OPERACIONES_2 / sizeof OPERACIONES_2[0]; j++)
    if (!strcmp(operador, OPERACIONES_2[j]))
    {
      *n1 = atoi(pila_desapilar(pila_int));
      *n2 = atoi(pila_desapilar(pila_int));
      *n_operandos = DOS_OPERANDOS;
      return true;
    }
  for (int j = 0; j < sizeof OPERACIONES_3 / sizeof OPERACIONES_3[0]; j++)
    if (!strcmp(operador, OPERACIONES_2[j]))
    {
      *n1 = atoi(pila_desapilar(pila_int));
      *n2 = atoi(pila_desapilar(pila_int));
      *n3 = atoi(pila_desapilar(pila_int));
      *n_operandos = TRES_OPERANDOS;
      return true;
    }
  return false;
}

int dc()
{
  FILE *fp = stdin;
  if (!fp)
  {
    printf("ERROR\n");
    return false;
  }

  char almacenamiento[MAX_CHAR_READ];
  pila_t *pila_int = pila_crear();
  if (!pila_int)
    return -1;
  while (fgets(almacenamiento, MAX_CHAR_READ, fp))
  {
    char **elementos = split(almacenamiento, ' ');
    int i = 0;
    while (elementos[i])
    {
      if (is_number(elementos[i]))
        pila_apilar(pila_int, elementos[i]);
      else
      {
        if (pila_esta_vacia(pila_int))
          break;
        char *operador = strtok(elementos[i], "\n");
        int n1, n2, n3, n_operandos = -1;
        int result = 0;
        desapilar_cantidad_necesaria(&n1, &n2, &n3, &n_operandos, operador, pila_int);
        switch (n_operandos)
        {
        case UN_OPERANDO:
          result = _sqrt(n1);
          pila_apilar(pila_int, &result);
          break;
        case DOS_OPERANDOS:
          if (!strcmp(operador, "log")) // log
            result = _log(n1, n2);
          else
          {
            char o = *operador;
            result = o == '+' ? (n1 + n2) : ((o == '-') ? (n1 - n2) : ((o == '*') ? (n1 * n2) : ((o == '/' && n2 != 0) ? (n1 / n2) : ((o == '^' && n2 >= 0) ? potencia(n1, n2) : 0))));
          }
          pila_apilar(pila_int, &result);
          break;
        case TRES_OPERANDOS:
          result = (n1 == 0) ? n3 : n2;
          pila_apilar(pila_int, &result);
          break;
        default:
          break;
        }
      }
      i++;
    }
    printf("answer: %d\n", *(int *)pila_desapilar(pila_int));
    printf("%s\n", almacenamiento);
  }

  fclose(fp);
  pila_destruir(pila_int);
  return 0;
}

int main(int argc, char *argv[])
{
  dc();
  return 0;
}