#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
void pruebas_pila_crear()
{
    printf("INICIO DE PRUEBAS CREAR PILA\n");
    pila_t *pila = NULL;
    print_test("Pila inicializada a NULL", pila == NULL);
    pila = pila_crear();
    print_test("Pila creada distinta a NULL", pila != NULL);
    pila_destruir(pila);
    print_test("la pila fue destruida", true);
}

int toInt(void *num)
{
    return *(int *)num;
}

void pruebas_pila_con_dos_elementos()
{
    printf("INICIO DE PRUEBAS DE PILA CON DOS ELEMENTOS\n");
    pila_t *pila = pila_crear();
    print_test("Pila creada distinta a NULL", pila != NULL);
    int n = 33;
    int n2 = 44;
    pila_apilar(pila, &n);
    pila_apilar(pila, &n2);
    print_test("desapilar pila igual a tope anterior", toInt(pila_ver_tope(pila)) == toInt(pila_desapilar(pila)));
    print_test("los elementos se mantienen al desapilar", toInt(pila_ver_tope(pila)) == 33);
    print_test("pila vacia == false", pila_esta_vacia(pila) == false);
    print_test("desapilar pila igual a tope anterior", toInt(pila_ver_tope(pila)) == toInt(pila_desapilar(pila)));
    print_test("pila esta vacia", pila_esta_vacia(pila) == true);
    print_test("desapilar pila vacía == NULL", pila_desapilar(pila) == NULL);
    pila_destruir(pila);
}

void _populate_pila(pila_t *pila, int size)
{
    int *arr = malloc(size * sizeof(int));
    for (int i = 1; i <= size; i++)
    {
        arr[i] = i;
        pila_apilar(pila, &arr[i]);
    }
}

void pruebas_de_volumen()
{
    printf("INICIO DE PRUEBAS DE VOLUMEN PILA\n");
    pila_t *pila = pila_crear();
    _populate_pila(pila, 1000);
    bool pila_mantiene_orden = true;
    while (!pila_esta_vacia(pila))
    {
        printf("%d\n", toInt(pila_ver_tope(pila)));
        if (toInt(pila_ver_tope(pila)) != toInt(pila_desapilar(pila)))
        {
            pila_mantiene_orden = false;
            break;
        }
    }
    print_test("pila mantiene orden", pila_mantiene_orden == true);
    pila_destruir(pila);
}

void pruebas_pila_alumno()
{
    pruebas_pila_crear();
    pruebas_pila_con_dos_elementos();
    pruebas_de_volumen();
}
