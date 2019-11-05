#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t buscar(const char* clave, char* claves[], size_t largo)
{
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (size_t) i;
    }
    return -1;
}

static void prueba_abb_insertar()
{
  abb_t *abb = abb_crear(strcmp, NULL);

  char *clave1 = "3", *valor1 = "guau";
  char *clave2 = "4", *valor2 = "miau";
  char *clave3 = "2", *valor3 = "mu";

  print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
  print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
  print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
  print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
  print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
  print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
  print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

  /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
  print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
  print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
  print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
  print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
  print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

  print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
  print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
  print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
  print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
  print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

  abb_destruir(abb);
}

static void prueba_abb_reemplazar()
{
  abb_t *abb = abb_crear(strcmp, NULL);

  char *clave1 = "1", *valor1a = "3", *valor1b = "5";
  char *clave2 = "2", *valor2a = "4", *valor2b = "6";

  /* Inserta 2 valores y luego los reemplaza */
  print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
  print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
  print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
  print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
  print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

  print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
  print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
  print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
  print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
  print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

  abb_destruir(abb);
}

void test_iter_externo()
{
  char *valores_in_order[] = { "1", "2", "4", "6", "10", NULL };
  char *claves[] = {"4", "2", "6", "10", "2", "1", NULL};
  char *valores[] = {"4", "2", "6", "10", "2", "1", NULL};

  abb_t *arbol = abb_crear(strcmp, NULL);

  for (int i = 0; i < 6; i++)
  {
    abb_guardar(arbol, claves[i], valores[i]);
  }

  abb_iter_t *iter = abb_iter_in_crear(arbol);

  size_t i = 0;
  while (!abb_iter_in_al_final(iter))
  {
    const char *actual = abb_iter_in_ver_actual(iter);
    printf("\n %s \n", actual);
    if (strcmp(actual, valores_in_order[i]) != 0) {
      print_test("Error, no son valores iguales", strcmp(actual, valores_in_order[i]) != 0);
    }
    abb_iter_in_avanzar(iter);
    i++;
  }

  abb_iter_in_destruir(iter);

  abb_destruir(arbol);
}

static void prueba_abb_iterar()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    /* Inserta 3 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;
    size_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Tercer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));
    
    printf("Borrando elementos\n");
    abb_borrar(abb, claves[0]);
    abb_borrar(abb, claves[1]);
    abb_borrar(abb, claves[2]);
    printf("Borrando elementos termino\n");

    print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);
    /* Inserta 3 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    printf("\n %s \n", abb_iter_in_ver_actual(iter));
    printf("\n %s \n", claves[0]);
    print_test("Ver actual es el primero", strcmp(abb_iter_in_ver_actual(iter), claves[0]) == 0);

    abb_iter_in_destruir(iter);


    abb_destruir(abb);
}

static void prueba_abb_iterar_volumen(size_t largo)
{
    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", i);
        valores[i] = i;
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok) break;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


static void prueba_abb_reemplazar_con_destruir()
{
    abb_t* abb = abb_crear(strcmp, free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    free(valor1b);
    free(valor2b);
    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}

static void prueba_abb_borrar()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));

    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave1));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave2));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_clave_vacia()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_valor_null()
{
    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}


void pruebas_abb_alumno()
{
  test_iter_externo();
  prueba_abb_insertar();
  prueba_abb_reemplazar();
  prueba_abb_reemplazar_con_destruir();
  prueba_abb_borrar();
  prueba_abb_clave_vacia();
  prueba_abb_valor_null();
  prueba_abb_iterar();
  prueba_abb_iterar_volumen(100);
}