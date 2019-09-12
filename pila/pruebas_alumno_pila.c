#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

int toInt(void *num)
{
    return *(int *)num;
}

void pruebas_pila_crear()
{
    printf("\nINICIO DE PRUEBAS CREAR PILA\n");
    pila_t *pila = NULL;
    print_test("Pila inicializada a NULL", pila == NULL);
    pila = pila_crear();
    print_test("Pila creada distinta a NULL", pila != NULL);
    pila_destruir(pila);
    print_test("la pila fue destruida", true);
}

void pruebas_pila_generales()
{
    printf("\nINICIO DE PRUEBAS GENERALES DE PILA\n");
    pila_t *pila = pila_crear();
    print_test("Pila creada distinta a NULL", pila != NULL);
    print_test("desapilar pila recien creada es valido", pila_desapilar(pila) == NULL);
    print_test("ver tope de pila recien creada es valido", pila_ver_tope(pila) == NULL);
    print_test("esta vacia de pila recien creada es true", pila_esta_vacia(pila) == true);

    int n = 33;
    int n2 = 44;
    print_test("apila entero 33", pila_apilar(pila, &n) == true);
    print_test("apila entero 44", pila_apilar(pila, &n2) == true);
    print_test("desapilar pila igual a tope anterior", toInt(pila_ver_tope(pila)) == toInt(pila_desapilar(pila)));
    print_test("los elementos se mantienen al desapilar", toInt(pila_ver_tope(pila)) == 33);
    print_test("pila vacia == false", pila_esta_vacia(pila) == false);
    print_test("desapilar pila igual a tope anterior", toInt(pila_ver_tope(pila)) == toInt(pila_desapilar(pila)));
    print_test("pila esta vacia", pila_esta_vacia(pila) == true);
    print_test("desapilar pila vacía == NULL", pila_desapilar(pila) == NULL);

    printf("\nINICIO DE PRUEBAS APILAR NULL\n");
    print_test("apila NUll", pila_apilar(pila, NULL) == true);
    print_test("tope == NUll", pila_ver_tope(pila) == NULL);
    print_test("desapilar == NULL", pila_desapilar(pila) == NULL);
    print_test("pila esta vacia", pila_esta_vacia(pila) == true);

    printf("\nINICIO DE PRUEBAS APILAR STRING\n");
    char palabra[20] = "😱 - seré apilado";
    print_test("apila palabra", pila_apilar(pila, palabra) == true);
    print_test("tope == '😱 - seré apilado'", pila_ver_tope(pila) == palabra);
    print_test("desapilar == '😱 - seré apilado'", pila_desapilar(pila) == palabra);
    print_test("pila esta vacia", pila_esta_vacia(pila) == true);

    pila_destruir(pila);
}

void pruebas_de_volumen()
{
    printf("\nINICIO DE PRUEBAS DE VOLUMEN PILA\n");
    pila_t *pila = pila_crear();
    int size = 1000;
    int *arr = malloc(size * sizeof(int));

    printf("-> prueba apilar %d elementos\n", size);
    bool pila_mantiene_topes = true;
    bool apila_correctamente = true;
    for (int i = 0; i < size; i++)
    {
        arr[i] = i;
        if (pila_apilar(pila, &arr[i]) == false)
            apila_correctamente = false;
        if (toInt(pila_ver_tope(pila)) != i)
            pila_mantiene_topes = false;
    }

    print_test("apilar funciona correctamente", apila_correctamente == true);
    print_test("pila mantiene topes al apilar", pila_mantiene_topes == true);
    print_test("pila no está vacía luego de apilar", pila_esta_vacia(pila) == false);

    printf("-> prueba desapilar %d elementos\n", size);
    pila_mantiene_topes = true;
    bool desapila_correctamente = true;
    for (int j = size - 1; j >= 0; j--)
    {
        if (toInt(pila_desapilar(pila)) != j)
            desapila_correctamente = false;
        if (pila_ver_tope(pila) != NULL && toInt(pila_ver_tope(pila)) != (j - 1))
            pila_mantiene_topes = false;
    }
    print_test("desapilar funciona correctamente", desapila_correctamente == true);
    print_test("pila mantiene topes al desapilar", pila_mantiene_topes == true);
    print_test("al desapilar todos los elementos la pila esta vacía", pila_esta_vacia(pila) == true);
    print_test("al desapilar todos los elementos el tope es NULL", pila_ver_tope(pila) == NULL);

    free(arr);
    pila_destruir(pila);
}

void prueba_destruir()
{
    printf("\nINICIO DE PRUEBAS PARA DESTRUIR PILA\n");
    pila_t *pila = pila_crear();
    pila_destruir(pila);
    int n = 42;

    pila_apilar(pila, &n);
}

void pruebas_pila_alumno()
{
    pruebas_pila_crear();
    pruebas_pila_generales();
    pruebas_de_volumen();
    prueba_destruir();
}
