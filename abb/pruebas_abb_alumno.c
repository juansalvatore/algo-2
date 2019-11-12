/*
 * prueba_abb.c
 * Pruebas para el tipo de dato abstracto Tabla de abb
 * Copyright: (2011) Margarita Manterola, Maximiliano Curia
 * Licencia: CC-BY-SA 2.5 (ar) ó CC-BY-SA 3.0
 */

#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For ssize_t in Linux.
#include <time.h>

#define VOLUMEN 1000

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

// static void prueba_crear_abb_vacio()
// {
//     abb_t *abb = abb_crear(strcmp, NULL);

//     print_test("Prueba abb crear abb vacio", abb);
//     print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
//     print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
//     print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
//     print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

//     abb_destruir(abb);
// }

// static void prueba_iterar_abb_vacio()
// {
//     abb_t *abb = abb_crear(strcmp, NULL);
//     abb_iter_t *iter = abb_iter_in_crear(abb);
//     print_test("Prueba abb iter crear iterador abb vacio", iter);
//     print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
//     print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
//     print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

//     abb_iter_in_destruir(iter);
//     abb_destruir(abb);
// }

// static void prueba_abb_insertar()
// {
//     abb_t *abb = abb_crear(strcmp, NULL);

//     char *clave1 = "perro", *valor1 = "guau";
//     char *clave2 = "gato", *valor2 = "miau";
//     char *clave3 = "vaca", *valor3 = "mu";

//     /* Inserta 1 valor y luego lo borra */
//     print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
//     print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
//     print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
//     print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
//     print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
//     print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
//     print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

//     /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
//     print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
//     print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
//     print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
//     print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
//     print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

//     print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
//     print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
//     print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
//     print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
//     print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

//     abb_destruir(abb);
// }

// static void prueba_abb_reemplazar()
// {
//     abb_t *abb = abb_crear(strcmp, NULL);

//     char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
//     char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

//     /* Inserta 2 valores y luego los reemplaza */
//     print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
//     print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
//     print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
//     print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
//     print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
//     print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
//     print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

//     print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
//     print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
//     print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
//     print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
//     print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
//     print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
//     print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

//     abb_destruir(abb);
// }

// static void prueba_abb_reemplazar_con_destruir()
// {
//     abb_t *abb = abb_crear(strcmp, free);

//     char *clave1 = "perro", *valor1a, *valor1b;
//     char *clave2 = "gato", *valor2a, *valor2b;

//     /* Pide memoria para 4 valores */
//     valor1a = malloc(10 * sizeof(char));
//     valor1b = malloc(10 * sizeof(char));
//     valor2a = malloc(10 * sizeof(char));
//     valor2b = malloc(10 * sizeof(char));

//     /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
//     print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
//     print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
//     print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
//     print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
//     print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
//     print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
//     print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

//     print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
//     print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
//     print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
//     print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
//     print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
//     print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
//     print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

//     /* Se destruye el abb (se debe liberar lo que quedó dentro) */
//     abb_destruir(abb);
// }

// static void prueba_abb_borrar()
// {
//     abb_t *abb = abb_crear(strcmp, NULL);

//     char *clave1 = "perro", *valor1 = "guau";
//     char *clave2 = "gato", *valor2 = "miau";
//     char *clave3 = "vaca", *valor3 = "mu";

//     /* Inserta 3 valores y luego los borra */
//     print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
//     print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
//     print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));

//     /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
//     print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
//     print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
//     print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
//     print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
//     print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
//     print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

//     print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
//     print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
//     print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave1));
//     print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
//     print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
//     print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

//     print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
//     print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
//     print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave2));
//     print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
//     print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
//     print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

//     abb_destruir(abb);
// }

// static void prueba_abb_clave_vacia()
// {
//     abb_t *abb = abb_crear(strcmp, NULL);

//     char *clave = "", *valor = "";

//     print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
//     print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
//     print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
//     print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
//     print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
//     print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

//     abb_destruir(abb);
// }

// static void prueba_abb_valor_null()
// {
//     abb_t *abb = abb_crear(strcmp, NULL);

//     char *clave = "", *valor = NULL;

//     /* Inserta 1 valor y luego lo borra */
//     print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
//     print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
//     print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
//     print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
//     print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
//     print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

//     abb_destruir(abb);
// }

// static void prueba_abb_volumen(size_t largo, bool debug)
// {
//     abb_t *abb = abb_crear(strcmp, NULL);

//     const size_t largo_clave = 10;
//     char(*claves)[largo_clave] = malloc(largo * largo_clave);

//     unsigned *valores[largo];

//     /* Inserta 'largo' parejas en el abb */
//     bool ok = true;
//     for (unsigned i = 0; i < largo; i++)
//     {
//         valores[i] = malloc(sizeof(int));
//         sprintf(claves[i], "%08d", i);
//         *valores[i] = i;
//         ok = abb_guardar(abb, claves[i], valores[i]);
//         if (!ok)
//             break;
//     }

//     if (debug)
//         print_test("Prueba abb almacenar muchos elementos", ok);
//     if (debug)
//         print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

//     /* Verifica que devuelva los valores correctos */
//     for (size_t i = 0; i < largo; i++)
//     {
//         ok = abb_pertenece(abb, claves[i]);
//         if (!ok)
//             break;
//         ok = abb_obtener(abb, claves[i]) == valores[i];
//         if (!ok)
//             break;
//     }

//     if (debug)
//         print_test("Prueba abb pertenece y obtener muchos elementos", ok);
//     if (debug)
//         print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

//     /* Verifica que borre y devuelva los valores correctos */
//     for (size_t i = 0; i < largo; i++)
//     {
//         ok = abb_borrar(abb, claves[i]) == valores[i];
//         if (!ok)
//             break;
//     }

//     if (debug)
//         print_test("Prueba abb borrar muchos elementos", ok);
//     if (debug)
//         print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

//     /* Destruye el abb y crea uno nuevo que sí libera */
//     abb_destruir(abb);
//     abb = abb_crear(strcmp, free);

//     /* Inserta 'largo' parejas en el abb */
//     ok = true;
//     for (size_t i = 0; i < largo; i++)
//     {
//         ok = abb_guardar(abb, claves[i], valores[i]);
//         if (!ok)
//             break;
//     }

//     free(claves);

//     /* Destruye el abb - debería liberar los enteros */
//     abb_destruir(abb);
// }

// static ssize_t buscar(const char *clave, char *claves[], size_t largo)
// {
//     for (size_t i = 0; i < largo; i++)
//     {
//         if (strcmp(clave, claves[i]) == 0)
//             return (ssize_t)i;
//     }
//     return -1;
// }

// static void prueba_abb_iterar()
// {
//     abb_t *abb = abb_crear(strcmp, NULL);

//     char *claves[] = {"perro", "gato", "vaca"};
//     char *valores[] = {"guau", "miau", "mu"};

//     /* Inserta 3 valores */
//     print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
//     print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
//     print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

//     // Prueba de iteración sobre las claves almacenadas.
//     abb_iter_t *iter = abb_iter_in_crear(abb);
//     const char *clave;
//     ssize_t indice;

//     print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

//     /* Primer valor */
//     clave = abb_iter_in_ver_actual(iter);
//     indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
//     print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
//     print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
//     print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
//     print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

//     /* Segundo valor */
//     clave = abb_iter_in_ver_actual(iter);
//     indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
//     print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
//     print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
//     print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
//     print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

//     /* Tercer valor */
//     clave = abb_iter_in_ver_actual(iter);
//     indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
//     print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
//     print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
//     abb_iter_in_avanzar(iter);
//     print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

//     /* Vuelve a tratar de avanzar, por las dudas */
//     print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
//     print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
//     print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

//     abb_iter_in_destruir(iter);
//     abb_destruir(abb);
// }

// static void prueba_abb_iterar_volumen(size_t largo)
// {
//     abb_t *abb = abb_crear(strcmp, NULL);

//     const size_t largo_clave = 10;
//     char(*claves)[largo_clave] = malloc(largo * largo_clave);

//     size_t valores[largo];

//     /* Inserta 'largo' parejas en el abb */
//     bool ok = true;
//     for (unsigned i = 0; i < largo; i++)
//     {
//         sprintf(claves[i], "%08d", i);
//         valores[i] = i;
//         ok = abb_guardar(abb, claves[i], &valores[i]);
//         if (!ok)
//             break;
//     }

//     // Prueba de iteración sobre las claves almacenadas.
//     abb_iter_t *iter = abb_iter_in_crear(abb);
//     print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

//     ok = true;
//     unsigned i;
//     const char *clave;
//     size_t *valor;

//     for (i = 0; i < largo; i++)
//     {
//         if (abb_iter_in_al_final(iter))
//         {
//             ok = false;
//             break;
//         }
//         clave = abb_iter_in_ver_actual(iter);
//         if (clave == NULL)
//         {
//             ok = false;
//             break;
//         }
//         valor = abb_obtener(abb, clave);
//         if (valor == NULL)
//         {
//             ok = false;
//             break;
//         }
//         *valor = largo;
//         abb_iter_in_avanzar(iter);
//     }
//     print_test("Prueba abb iteración en volumen", ok);
//     print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
//     print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

//     ok = true;
//     for (i = 0; i < largo; i++)
//     {
//         if (valores[i] != largo)
//         {
//             ok = false;
//             break;
//         }
//     }
//     print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

//     free(claves);
//     abb_iter_in_destruir(iter);
//     abb_destruir(abb);
// }

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL (copiadas)
 * *****************************************************************/

// int comparar_numeros(const char *str1, const char *str2)
// {

//     if (atoi(str1) > atoi(str2))
//         return -1;
//     else if (atoi(str1) < atoi(str2))
//         return 1;
//     else
//         return 0;
// }

// void test_crear()
// {

//     abb_t *arbol = abb_crear(strcmp, NULL);

//     char *clave_1 = "14";
//     char *dato_1 = "Perro";

//     char *clave_2 = "9";
//     char *dato_2 = "Gato";

//     char *clave_3 = "1";
//     char *dato_3 = "Jirafa";

//     print_test("Obtener es NULL", abb_obtener(arbol, clave_1) == NULL);
//     print_test("Borrar es NULL", abb_borrar(arbol, clave_1) == NULL);

//     print_test("Guardar elemento 1", abb_guardar(arbol, clave_1, dato_1));
//     print_test("Obtener elemento 1", abb_obtener(arbol, clave_1) == dato_1);
//     print_test("Cantidad es 1", abb_cantidad(arbol) == 1);

//     print_test("Guardar elemento 2", abb_guardar(arbol, clave_2, dato_2));
//     print_test("Obtener elemento 2", abb_obtener(arbol, clave_2) == dato_2);
//     print_test("Cantidad es 2", abb_cantidad(arbol) == 2);

//     print_test("Guardar elemento 3", abb_guardar(arbol, clave_3, dato_3));
//     print_test("Obtener elemento 3", abb_obtener(arbol, clave_3) == dato_3);
//     print_test("Cantidad es 3", abb_cantidad(arbol) == 3);

//     print_test("Pertenece 1", abb_pertenece(arbol, clave_1));
//     print_test("Pertenece 2", abb_pertenece(arbol, clave_2));
//     print_test("Pertenece 3", abb_pertenece(arbol, clave_3));

//     printf("Inorder: \n");
//     abb_in_order(arbol, NULL, NULL);

//     print_test("Borrar 1 (raiz)", abb_borrar(arbol, clave_1) == dato_1);
//     print_test("Cantidad es 2", abb_cantidad(arbol) == 2);

//     printf("Inorder: \n");
//     abb_in_order(arbol, NULL, NULL);

//     print_test("Obtener elemento 2", abb_obtener(arbol, clave_2) == dato_2);

//     print_test("Borrar 2", abb_borrar(arbol, clave_2) == dato_2);
//     print_test("Cantidad es 1", abb_cantidad(arbol) == 1);

//     printf("Inorder: \n");
//     abb_in_order(arbol, NULL, NULL);

//     print_test("Borrar 3", abb_borrar(arbol, clave_3) == dato_3);
//     print_test("Cantidad es 0", abb_cantidad(arbol) == 0);

//     abb_destruir(arbol);
// }

// void test_reemplazar()
// {

//     char *claves[] = {"1", "2", "3", "4", "5", "6", "7", NULL};
//     char *valores[] = {"1", "2", "3", "4", "5", "6", "7", NULL};

//     abb_t *arbol = abb_crear(comparar_numeros, NULL);

//     for (int i = 0; i < 7; i++)
//     {
//         abb_guardar(arbol, claves[i], valores[i]);
//     }

//     //abb_in_order(arbol, NULL, NULL);

//     abb_destruir(arbol);
// }

// void test_iter_externo()
// {

//     char *claves[] = {"1", "2", "3", "4", "5", "6", "7", NULL};
//     char *valores[] = {"1", "2", "3", "4", "5", "6", "7", NULL};

//     abb_t *arbol = abb_crear(comparar_numeros, NULL);

//     for (int i = 0; i < 7; i++)
//     {
//         abb_guardar(arbol, claves[i], valores[i]);
//     }

//     abb_iter_t *iter = abb_iter_in_crear(arbol);

//     while (!abb_iter_in_al_final(iter))
//     {

//         printf("%s\n", abb_iter_in_ver_actual(iter));

//         abb_iter_in_avanzar(iter);
//     }

//     abb_iter_in_destruir(iter);

//     abb_destruir(arbol);
// }

// // pruebas copiadas

// static void prueba_crear_abb_vacio()
// {
//     printf("\nPRUEBAS ABB VACIO\n");
//     abb_t *abb = abb_crear(strcmp, NULL);

//     print_test("Prueba abb crear abb vacio", abb);
//     print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
//     print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
//     print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
//     print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

//     abb_destruir(abb);
// }

// static void prueba_iterar_abb_vacio()
// {
//     printf("\nPRUEBAS ITERAR EN ABB VACIO\n");
//     abb_t *abb = abb_crear(strcmp, NULL);
//     abb_iter_t *iter = abb_iter_in_crear(abb);
//     print_test("Prueba abb iter crear iterador abb vacio", iter);
//     print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
//     print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
//     print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

//     abb_iter_in_destruir(iter);
//     abb_destruir(abb);
// }

// static void prueba_abb_insertar()
// {
//     printf("\nPRUEBAS INSERTAR\n");
//     abb_t *abb = abb_crear(strcmp, NULL);

//     char *clave1 = "perro", *valor1 = "guau";
//     char *clave2 = "gato", *valor2 = "miau";
//     char *clave3 = "vaca", *valor3 = "mu";

//     // Inserta 1 valor y luego lo borra
//     print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
//     print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
//     print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
//     print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
//     print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
//     print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

//     //Inserta otros 2 valores y no los borra (se destruyen con el abb)
//     print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
//     print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
//     print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
//     print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

//     print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
//     print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
//     print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
//     print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

//     abb_destruir(abb);
// }

// static void prueba_abb_reemplazar()
// {
//     printf("\nPRUEBAS REEMPLAZAR DATO\n");
//     abb_t *abb = abb_crear(strcmp, NULL);

//     char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
//     char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

//     // Inserta 2 valores y luego los reemplaza
//     print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
//     print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
//     print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
//     print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
//     print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

//     print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
//     print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
//     print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
//     print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
//     print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

//     abb_destruir(abb);
// }

// static void prueba_abb_reemplazar_con_destruir()
// {
//     printf("\nPRUEBAS REEMPLAZAR DATOS DINAMICOS\n");
//     abb_t *abb = abb_crear(strcmp, free);

//     char *clave1 = "perro", *valor1a, *valor1b;
//     char *clave2 = "gato", *valor2a, *valor2b;

//     // Pide memoria para 4 valores
//     valor1a = malloc(10 * sizeof(char));
//     valor1b = malloc(10 * sizeof(char));
//     valor2a = malloc(10 * sizeof(char));
//     valor2b = malloc(10 * sizeof(char));

//     // Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza)
//     print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
//     print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
//     print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
//     print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
//     print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
//     print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
//     print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

//     print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
//     print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
//     print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
//     print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
//     print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
//     print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
//     print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

//     // Se destruye el abb (se debe liberar lo que quedó dentro)
//     abb_destruir(abb);
// }

// static void prueba_abb_borrar()
// {
//     printf("\nPRUEBAS BORRAR\n");
//     abb_t *abb = abb_crear(strcmp, NULL);

//     char *clave1 = "2", *valor1 = "guau";
//     char *clave2 = "1", *valor2 = "miau";
//     char *clave3 = "3", *valor3 = "mu";
//     char *clave4 = "4", *valor4 = "hola";

//     // Inserta 3 valores y luego los borra
//     print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
//     print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
//     print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
//     print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));

//     // Al borrar cada elemento comprueba que ya no está pero los otros sí.
//     print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
//     print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
//     print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave1));
//     print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
//     print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
//     print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);

//     print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
//     print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
//     print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
//     print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
//     print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
//     print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

//     print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
//     print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
//     print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave2));
//     print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
//     print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
//     print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

//     abb_destruir(abb);
// }

// static void prueba_abb_clave_vacia()
// {
//     printf("\nPRUEBAS CLAVE VACIA\n");
//     abb_t *abb = abb_crear(strcmp, NULL);

//     char *clave = "", *valor = "";

//     print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
//     print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
//     print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
//     print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
//     print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
//     print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

//     abb_destruir(abb);
// }

// static void prueba_abb_valor_null()
// {
//     printf("\nPRUEBAS GUARDAR ELEMENTO NULL\n");
//     abb_t *abb = abb_crear(strcmp, NULL);

//     char *clave = "", *valor = NULL;

//     // Inserta 1 valor y luego lo borra
//     print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
//     print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
//     print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
//     print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
//     print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
//     print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

//     abb_destruir(abb);
// }

// static void prueba_abb_volumen(size_t largo, bool debug)
// {
//     printf("\nPRUEBAS VOLUMEN\n");
//     abb_t *abb = abb_crear(strcmp, NULL);

//     const size_t largo_clave = 10;
//     char(*claves)[largo_clave] = malloc(largo * largo_clave);

//     unsigned *valores[largo];
//     unsigned int claves_HC[9] = {5000, 2000, 6000, 1000, 7000, 3000, 8000, 4000, 9000};
//     // Inserta 'largo' parejas en el abb
//     bool ok = true;
//     for (unsigned i = 0; i < largo; i++)
//     {
//         valores[i] = malloc(sizeof(int));
//         sprintf(claves[i], "%08d", (unsigned int)(claves_HC[i % 8] + i));
//         *valores[i] = i;
//         ok = abb_guardar(abb, claves[i], valores[i]);
//         if (!ok)
//             break;
//     }

//     if (debug)
//         print_test("Prueba abb almacenar muchos elementos", ok);
//     if (debug)
//         print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

//     // Verifica que devuelva los valores correctos
//     for (size_t i = 0; i < largo; i++)
//     {
//         ok = abb_pertenece(abb, claves[i]);
//         if (!ok)
//             break;
//         ok = abb_obtener(abb, claves[i]) == valores[i];
//         if (!ok)
//             break;
//     }

//     if (debug)
//         print_test("Prueba abb pertenece y obtener muchos elementos", ok);
//     if (debug)
//         print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

//     // Verifica que borre y devuelva los valores correctos
//     for (size_t i = 0; i < largo; i++)
//     {
//         ok = abb_borrar(abb, claves[i]) == valores[i];
//         if (!ok)
//             break;
//     }

//     if (debug)
//         print_test("Prueba abb borrar muchos elementos", ok);
//     if (debug)
//         print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

//     // Destruye el abb y crea uno nuevo que sí libera
//     abb_destruir(abb);
//     abb = abb_crear(strcmp, free);

//     // Inserta 'largo' parejas en el abb
//     ok = true;
//     for (size_t i = 0; i < largo; i++)
//     {
//         ok = abb_guardar(abb, claves[i], valores[i]);
//         if (!ok)
//             break;
//     }

//     free(claves);

//     // Destruye el abb - debería liberar los enteros
//     abb_destruir(abb);
// }

// static ssize_t buscar(const char *clave, char *claves[], size_t largo)
// {
//     for (size_t i = 0; i < largo; i++)
//     {
//         if (strcmp(clave, claves[i]) == 0)
//             return (ssize_t)i;
//     }
//     return -1;
// }

// static void prueba_abb_iterar()
// {
//     printf("\nPRUEBAS ITERAR\n");
//     abb_t *abb = abb_crear(strcmp, NULL);

//     char *claves[] = {"perro", "gato", "vaca"};
//     char *valores[] = {"guau", "miau", "mu"};

//     // Inserta 3 valores
//     print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
//     print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
//     print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

//     // Prueba de iteración sobre las claves almacenadas.
//     abb_iter_t *iter = abb_iter_in_crear(abb);
//     const char *clave;
//     ssize_t indice;

//     print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

//     // Primer valor
//     clave = abb_iter_in_ver_actual(iter);
//     indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
//     print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
//     print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
//     print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
//     print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

//     // Segundo valor
//     clave = abb_iter_in_ver_actual(iter);
//     indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
//     print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
//     print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
//     print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
//     print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

//     // Tercer valor
//     clave = abb_iter_in_ver_actual(iter);
//     indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
//     print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
//     print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
//     abb_iter_in_avanzar(iter);
//     print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

//     // Vuelve a tratar de avanzar, por las dudas
//     print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
//     print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
//     print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

//     abb_iter_in_destruir(iter);
//     abb_destruir(abb);
// }

// static void prueba_abb_iterar_volumen(size_t largo)
// {
//     printf("\nPRUEBAS ITERAR VOLUMEN\n");
//     abb_t *abb = abb_crear(strcmp, NULL);

//     const size_t largo_clave = 10;
//     char(*claves)[largo_clave] = malloc(largo * largo_clave);

//     size_t valores[largo];

//     // Inserta 'largo' parejas en el abb
//     bool ok = true;
//     unsigned int claves_HC[9] = {5000, 2000, 6000, 1000, 7000, 3000, 8000, 4000, 9000};

//     for (unsigned i = 0; i < largo; i++)
//     {
//         sprintf(claves[i], "%08d", (unsigned int)(claves_HC[i % 8] + i));
//         valores[i] = i;
//         ok = abb_guardar(abb, claves[i], &valores[i]);
//         if (!ok)
//             break;
//     }

//     // Prueba de iteración sobre las claves almacenadas.
//     abb_iter_t *iter = abb_iter_in_crear(abb);
//     print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

//     ok = true;
//     unsigned i;
//     const char *clave;
//     size_t *valor;

//     for (i = 0; i < largo; i++)
//     {
//         if (abb_iter_in_al_final(iter))
//         {
//             ok = false;
//             break;
//         }
//         clave = abb_iter_in_ver_actual(iter);
//         if (clave == NULL)
//         {
//             ok = false;
//             break;
//         }
//         valor = abb_obtener(abb, clave);
//         if (valor == NULL)
//         {
//             ok = false;
//             break;
//         }
//         *valor = largo;
//         abb_iter_in_avanzar(iter);
//     }
//     print_test("Prueba abb iteración en volumen", ok);
//     print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
//     print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

//     ok = true;
//     for (i = 0; i < largo; i++)
//     {
//         if (valores[i] != largo)
//         {
//             ok = false;
//             break;
//         }
//     }
//     print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

//     free(claves);
//     abb_iter_in_destruir(iter);
//     abb_destruir(abb);
// }

// bool sumar_todos(const char *clave, void *dato, void *extra)
// {
//     *(int *)extra += *(int *)dato;
//     return true;
// }

// bool sumar_clave_menor_6(const char *clave, void *dato, void *extra)
// {
//     if (strcmp(clave, "6") > 0)
//     {
//         return false;
//     }
//     *(int *)extra += *(int *)dato;
//     return true;
// }

// static void pruebas_iterador_interno()
// {
//     printf("\nPRUEBAS ITERADOR INTERNO\n");
//     abb_t *abb = abb_crear(strcmp, NULL);
//     char *clave1 = "5";
//     int valor1 = 3;
//     char *clave2 = "1";
//     int valor2 = 2;
//     char *clave3 = "7";
//     int valor3 = 1;

//     abb_guardar(abb, clave1, &valor1);
//     abb_guardar(abb, clave2, &valor2);
//     abb_guardar(abb, clave3, &valor3);

//     int suma = 0;
//     abb_in_order(abb, sumar_todos, &suma);
//     print_test("Iterar sin corte es correcto", suma == 6);

//     suma = 0;
//     abb_in_order(abb, sumar_clave_menor_6, &suma);
//     print_test("Iterar con corte es correcto", suma == 5);

//     abb_destruir(abb);
// }

// COPIADAS 3

static void prueba_crear_abb_vacio()
{
    printf("\n prueba_crear_abb_vacio \n");
    abb_t *abb = abb_crear(NULL, NULL);

    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);
}

static void prueba_iterar_abb_vacio()
{
    printf("\n prueba_iterar_abb_vacio \n");
    abb_t *abb = abb_crear(NULL, NULL);
    abb_iter_t *iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_insertar()
{
    printf("\n prueba_abb_insertar \n");
    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 1 valor y luego lo borra */
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
    printf("\n prueba_abb_reemplazar \n");
    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    /* Inserta 2 valores y luego los reemplaza */
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

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir()
{
    printf("\n prueba_abb_reemplazar_con_destruir \n");
    abb_t *abb = abb_crear(strcmp, free);

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

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}

static void prueba_abb_borrar()
{
    printf("\n prueba_abb_borrar \n");
    abb_t *abb = abb_crear(strcmp, NULL);

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
    printf("\n prueba_abb_clave_vacia \n");
    abb_t *abb = abb_crear(strcmp, NULL);

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
    printf("\n prueba_abb_valor_null \n");
    abb_t *abb = abb_crear(strcmp, NULL);

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

static void prueba_abb_volumen(size_t largo, bool debug)
{
    printf("\n prueba_abb_volumen \n");
    abb_t *abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char(*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t *valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    int i = 0;
    while (ok && i < largo)
    {
        size_t j = (size_t)rand() % largo;
        sprintf(claves[i], "%lu", j);
        if (abb_pertenece(abb, claves[i]))
            continue;
        valores[i] = malloc(sizeof(size_t));
        *valores[i] = j;
        ok = abb_guardar(abb, claves[i], valores[i]);
        i++;
    }

    if (debug)
        print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug)
        print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que devuelva los valores correctos */
    for (i = 0; i < largo; i++)
    {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok)
            break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok)
            break;
    }

    if (debug)
        print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug)
        print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (i = 0; i < largo; i++)
    {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok)
            break;
    }

    if (debug)
        print_test("Prueba abb borrar muchos elementos", ok);
    if (debug)
        print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Destruye el abb y crea uno nuevo que sí libera */
    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    /* Inserta 'largo' parejas en el abb */
    ok = true;
    for (i = 0; i < largo; i++)
    {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok)
            break;
    }

    free(claves);

    /* Destruye el abb - debería liberar los enteros */
    abb_destruir(abb);
}

static ssize_t buscar(const char *clave, char *claves[], size_t largo)
{
    for (size_t i = 0; i < largo; i++)
    {
        if (strcmp(clave, claves[i]) == 0)
            return (ssize_t)i;
    }
    return -1;
}

static void prueba_abb_iterar()
{
    printf("\n prueba_abb_iterar \n");
    abb_t *abb = abb_crear(strcmp, NULL);

    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};

    /* Inserta 3 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t *iter = abb_iter_in_crear(abb);
    const char *clave;
    ssize_t indice;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));
    print_test("Prueba abb iterador el actual es mayor al anterior", strcmp(clave, abb_iter_in_ver_actual(iter)) < 0);

    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));
    print_test("Prueba abb iterador el actual es mayor al anterior", strcmp(clave, abb_iter_in_ver_actual(iter)) < 0);

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

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_iterar_volumen(size_t largo)
{
    printf("\n prueba_abb_iterar_volumen \n");
    abb_t *abb = abb_crear(strcmp, free);

    const size_t largo_clave = 10;
    char(*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t *valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    int i = 0;
    while (ok && i < largo)
    {
        size_t j = (size_t)rand() % largo;
        sprintf(claves[i], "%lu", j);
        if (abb_pertenece(abb, claves[i]))
            continue;
        valores[i] = malloc(sizeof(size_t));
        *valores[i] = j;
        ok = abb_guardar(abb, claves[i], valores[i]);
        i++;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t *iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    i = 0;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++)
    {
        if (abb_iter_in_al_final(iter))
        {
            ok = false;
            break;
        }
        if (i > 0 && !(strcmp(clave, abb_iter_in_ver_actual(iter)) < 0))
        {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if (clave == NULL)
        {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if (valor == NULL)
        {
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
    for (i = 0; i < largo; i++)
    {
        if (*valores[i] != largo)
        {
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

bool _sumatoria_hasta_v(const char *clave, int *dato, int *contador)
{
    if (strcmp(clave, "v") > 0)
        return false;
    printf("\n %s \n", clave);
    (*contador) += clave[0];
    return true;
}

bool sumatoria_hasta_v(const char *clave, void *dato, void *contador)
{
    return _sumatoria_hasta_v(clave, dato, contador);
}

bool _sumatoria_hasta_a(const char *clave, int *dato, int *contador)
{
    if (strcmp(clave, "a") > 0)
        return false;
    printf("\n %s \n", clave);
    (*contador) += clave[0];
    return true;
}

bool sumatoria_hasta_a(const char *clave, void *dato, void *contador)
{
    return _sumatoria_hasta_a(clave, dato, contador);
}

void pruebas_iterador_interno_sin_corte()
{
    printf("\n pruebas_iterador_interno_sin_corte \n");
    abb_t *abb = abb_crear(strcmp, free);

    char *vector[10] = {"h", "d", "a", "f", "m", "j", "l", "v", "r", "t"};

    for (int i = 0; i < 10; i++)
    {
        int *n = malloc(sizeof(int));
        *n = i;
        abb_guardar(abb, vector[i], n);
    }

    int contador = 0;
    abb_in_order(abb, sumatoria_hasta_v, &contador);
    print_test("Prueba abb iterador interno sin corte", contador == 1074);
    abb_destruir(abb);
}

void pruebas_iterador_interno_con_corte()
{
    printf("\n pruebas_iterador_interno_con_corte \n");
    abb_t *abb = abb_crear(strcmp, free);

    char *vector[14] = {"h", "d", "a", "w", "f", "m", "x", "j", "l", "v", "y", "r", "t", "z"};

    for (int i = 0; i < 14; i++)
    {
        int *n = malloc(sizeof(int));
        *n = i;
        abb_guardar(abb, vector[i], n);
    }

    int contador = 0;
    abb_in_order(abb, sumatoria_hasta_v, &contador);
    print_test("Prueba abb iterador interno con corte", contador == 1074);
    contador = 0;
    abb_in_order(abb, sumatoria_hasta_a, &contador);
    printf("\n %d \n", contador);
    // print_test("Prueba abb iterador interno con corte en rama izquierda", 1 == 1);
    abb_destruir(abb);
}

void pruebas_abb_alumno()
{
    /* Ejecuta todas las pruebas unitarias. */
    // prueba_crear_abb_vacio();
    // prueba_iterar_abb_vacio();
    // prueba_abb_insertar();
    // prueba_abb_reemplazar();
    // prueba_abb_reemplazar_con_destruir();
    // prueba_abb_borrar();
    // prueba_abb_clave_vacia();
    // prueba_abb_valor_null();
    // prueba_abb_volumen(1000, true);
    // prueba_abb_iterar();
    // prueba_abb_iterar_volumen(1000);

    // pruebas copiadas
    // test_crear();
    // test_reemplazar();
    // test_iter_externo();

    //copiadas 2
    // prueba_crear_abb_vacio();
    // prueba_iterar_abb_vacio();
    // prueba_abb_insertar();
    // prueba_abb_reemplazar();
    // prueba_abb_reemplazar_con_destruir();
    // prueba_abb_borrar();
    // prueba_abb_clave_vacia();
    // prueba_abb_valor_null();
    // prueba_abb_volumen(1000, true);
    // prueba_abb_iterar();
    // prueba_abb_iterar_volumen(1000);
    // pruebas_iterador_interno();

    // copiadas 3
    srand((unsigned int)time(NULL));
    prueba_crear_abb_vacio();
    prueba_iterar_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_borrar();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null();
    prueba_abb_volumen(VOLUMEN, true);
    prueba_abb_iterar();
    prueba_abb_iterar_volumen(VOLUMEN);
    pruebas_iterador_interno_sin_corte();
    pruebas_iterador_interno_con_corte();
}

void pruebas_volumen_catedra(size_t largo)
{
    prueba_abb_volumen(largo, false);
}
