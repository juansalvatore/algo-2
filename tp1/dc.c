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
  int ini = 0, fin = n, medio = -1;
  for (int i = 0; i <= fin; i++)
  {
    medio = (ini + fin) / 2;
    if (medio * medio == n)
      return medio;
    if (medio * medio > n)
      fin = medio;
    else
      ini = medio;
  }
  return medio;
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

bool desapilar_cantidad_necesaria(int *n1, int *n2, int *n3, int *n_operandos, char *operador, pila_t *pila_int)
{
  if (pila_esta_vacia(pila_int))
    return false;
  for (int j = 0; j < sizeof OPERACIONES_1 / sizeof OPERACIONES_1[0]; j++)
    if (!strcmp(operador, OPERACIONES_1[j]))
    {
      char *c_n1 = pila_desapilar(pila_int);
      *n1 = atoi(c_n1);
      free(c_n1);
      *n_operandos = UN_OPERANDO;
      return true;
    }
  for (int j = 0; j < sizeof OPERACIONES_2 / sizeof OPERACIONES_2[0]; j++)
    if (!strcmp(operador, OPERACIONES_2[j]))
    {
      char *c_n1 = pila_desapilar(pila_int);
      if (pila_esta_vacia(pila_int))
        return false;
      char *c_n2 = pila_desapilar(pila_int);
      *n1 = atoi(c_n1);
      *n2 = atoi(c_n2);
      free(c_n1);
      free(c_n2);
      *n_operandos = DOS_OPERANDOS;
      return true;
    }
  for (int j = 0; j < sizeof OPERACIONES_3 / sizeof OPERACIONES_3[0]; j++)
    if (!strcmp(operador, OPERACIONES_3[j]))
    {
      char *c_n1 = pila_desapilar(pila_int);
      if (pila_esta_vacia(pila_int))
        return false;
      char *c_n2 = pila_desapilar(pila_int);
      if (pila_esta_vacia(pila_int))
        return false;
      char *c_n3 = pila_desapilar(pila_int);
      *n1 = atoi(c_n1);
      *n2 = atoi(c_n2);
      *n3 = atoi(c_n3);
      free(c_n1);
      free(c_n2);
      free(c_n3);
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
  if (pila_int == NULL)
  {
    printf("ERROR\n");
    return -1;
  }
  bool hay_error = false;
  if (!pila_int)
    return -1;
  while (fgets(almacenamiento, MAX_CHAR_READ, fp))
  {
    char **elementos = split(almacenamiento, ' ');
    char *str_result = malloc(40 * sizeof(char));
    if (!str_result)
    {
      free(elementos);
      break;
    }
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
        if (!operador)
        {
          i++;
          continue;
        }
        char o = *operador;
        int n1, n2, n3, n_operandos = -1;
        int result = 0;
        hay_error = !desapilar_cantidad_necesaria(&n1, &n2, &n3, &n_operandos, operador, pila_int);
        if (!hay_error)
        {
          switch (n_operandos)
          {
          case UN_OPERANDO:
            if (n1 < 0)
              hay_error = true;
            else
            {
              result = _sqrt(n1);
              hay_error = false;
            }
            break;
          case DOS_OPERANDOS:
            hay_error = !operacion_algebraica(o, operador, n1, n2, &result);
            break;
          case TRES_OPERANDOS:
            result = n1 == 0 ? n3 : n2;
            hay_error = false;
            break;
          default:
            break;
          }
          if (n_operandos != -1 && !hay_error)
          {
            sprintf(str_result, "%d", result);
            pila_apilar(pila_int, _copiar_string(str_result));
          }
        }
        free(operador);
      }
      i++;
    }
    free(str_result);
    free_strv(elementos);
    char *result = (char *)pila_desapilar(pila_int);
    if (pila_esta_vacia(pila_int) && !hay_error)
      printf("%s\n", result);
    else
      printf("ERROR\n");
    free(result);
  }
  fclose(fp);
  while (!pila_esta_vacia(pila_int))
    free(pila_desapilar(pila_int));
  pila_destruir(pila_int);
  return 0;
}

int main(int argc, char *argv[])
{
  dc();
  return 0;
}