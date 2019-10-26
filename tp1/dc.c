#include "dc.h"
#include "pila.h"
#include "strutil.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_READ 400

bool is_number(char *str)
{
  if (atoi(str) == 0 && str[0] != '0')
    return false;
  return true;
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
      {  
        pila_apilar(pila_int, elementos[i]);
      }
      else
      {
        if (pila_esta_vacia(pila_int))
          break;
        char *operador =strtok(elementos[i], "\n") ;
        
        printf("test");
        if (strcmp(operador, "?") != 0)
        {
          int n1 = atoi(pila_desapilar(pila_int));
          int n2 = atoi(pila_desapilar(pila_int));
          int n3 = atoi(pila_desapilar(pila_int));
          int result = (n1 == 0) ? n3 : n2;
          printf("%d\n", result);
          break;
        }
      }
      i++;
    }
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