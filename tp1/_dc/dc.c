#include "dc.h"
#include "pila.h"
#include "strutil.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_READ 400
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

int potencia(int n, int e)
{
  if (e == 0)
    return 1;
  int temp = potencia(n, e / 2);
  if (e % 2 == 0)
    return temp * temp;
  else
    return n * temp * temp;
}

int _sqrt(int n)
{
  int ini = 1, fin = n, medio;

  while (ini <= fin)
  {
    medio = (ini + fin) / 2;
    if (medio * medio == n)
      return medio;
    if (medio * medio > n)
      fin = medio - 1;
    else
      ini = medio + 1;
  }
  return fin;
}

bool operacion_algebraica(char o, char *operador, int n1, int n2, int *result)
{
  if (o == '+')
  {
    *result = n1 + n2;
    return true;
  }
  else if (o == '-')
  {
    *result = n1 - n2;
    return true;
  }
  else if (o == '*')
  {
    *result = n1 * n2;
    return true;
  }
  else if (o == '/')
  {
    if (n2 == 0)
      return false;
    *result = n1 / n2;
    return true;
  }
  else if (o == '^')
  {
    if (n2 < 0)
      return false;
    *result = potencia(n1, n2);
    return true;
  }
  else if (!strcmp(operador, "log"))
  {
    if (n2 <= 1)
      return false;
    *result = _log(n1, n2);
    return true;
  }
  return false;
}

bool desapilar_cantidad_necesaria(char **n1, char **n2, char **n3, int *n_operandos, char *operador, pila_t *pila_int)
{
  if (pila_esta_vacia(pila_int))
    return false;

  *n1 = pila_desapilar(pila_int);
  if (!strcmp(operador, "sqrt"))
  {
    *n_operandos = UN_OPERANDO;
    return true;
  }
  else if (!strcmp(operador, "+") || !strcmp(operador, "-") || !strcmp(operador, "*") || !strcmp(operador, "/") || !strcmp(operador, "^") || !strcmp(operador, "log"))
  {
    if (pila_esta_vacia(pila_int))
      return false;
    *n2 = pila_desapilar(pila_int);
    *n_operandos = DOS_OPERANDOS;
    return true;
  }
  else if (!strcmp(operador, "?"))
  {
    if (pila_esta_vacia(pila_int))
      return false;
    *n2 = pila_desapilar(pila_int);
    if (pila_esta_vacia(pila_int))
      return false;
    *n3 = pila_desapilar(pila_int);
    *n_operandos = TRES_OPERANDOS;
    return true;
  }
  return false;
}

bool _calcular(char *n1, char *n2, char *n3, int n_operandos, char *operador, pila_t *pila_int)
{
  int result = 0;
  bool calc_ok = false;
  char o = *operador;

  switch (n_operandos)
  {
  case UN_OPERANDO:
    if (atoi(n1) >= 0)
    {
      result = _sqrt(atoi(n1));
      calc_ok = true;
    }
    break;
  case DOS_OPERANDOS:
    calc_ok = operacion_algebraica(o, operador, atoi(n1), atoi(n2), &result);
    break;
  case TRES_OPERANDOS:
    result = atoi(n1) == 0 ? atoi(n3) : atoi(n2);
    calc_ok = true;
    break;
  default:
    break;
  }

  char *str_result = malloc(40 * sizeof(char));
  if (calc_ok)
  {
    sprintf(str_result, "%d", result);
    pila_apilar(pila_int, _copiar_string(str_result));
  }

  if (n1)
    free(n1);
  if (n2)
    free(n2);
  if (n3)
    free(n3);
  free(str_result);
  return calc_ok;
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
  if (pila_int == NULL)
  {
    printf("ERROR\n");
    return -1;
  }
  if (!pila_int)
    return -1;

  bool archivo_vacio = true;
  while (fgets(almacenamiento, MAX_CHAR_READ, fp))
  {
    archivo_vacio = false;
    bool hay_error = false;
    char **elementos = split(almacenamiento, ' ');

    for (int i = 0; elementos[i] && !hay_error; i++)
    {
      if (!strcmp(elementos[i], "") && !strcmp(elementos[i], "\n"))
        continue;
      if (is_number(elementos[i]))
        pila_apilar(pila_int, _copiar_string(elementos[i]));
      else
      {
        char *operador = strtok(elementos[i], "\n");
        if (!operador)
          continue;
        char *n1 = NULL;
        char *n2 = NULL;
        char *n3 = NULL;
        int n_operandos = -1;
        hay_error = !desapilar_cantidad_necesaria(&n1, &n2, &n3, &n_operandos, operador, pila_int);
        hay_error = !_calcular(n1, n2, n3, n_operandos, operador, pila_int);
      }
    }

    char *result = (char *)pila_desapilar(pila_int);
    if (pila_esta_vacia(pila_int) && result != NULL && !hay_error)
      printf("%s\n", result);
    else
      printf("ERROR\n");

    while (!pila_esta_vacia(pila_int))
      free(pila_desapilar(pila_int));

    if (result != NULL)
      free(result);
    free_strv(elementos);
  }
  if (archivo_vacio)
    printf("ERROR\n");

  pila_destruir(pila_int);

  return 0;
}

int main(int argc, char *argv[])
{
  dc();
  return 0;
}