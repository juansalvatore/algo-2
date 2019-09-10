#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

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

void pruebas_pila_destruir()
{
    printf("INICIO DE PRUEBAS DESTRUIR PILA\n");
    pila_t *pila = pila_crear();
    print_test("Pila creada distinta a NULL", pila != NULL);
    int n = 33;
    int n2 = 44;
    pila_apilar(pila, &n);
    pila_apilar(pila, &n);
    pila_apilar(pila, &n);
    pila_apilar(pila, &n);
    pila_apilar(pila, &n);
    pila_apilar(pila, &n);
    pila_apilar(pila, &n);
    pila_apilar(pila, &n2);
    void *tope = pila_desapilar(pila);
    print_test("Pila desapilar pila igual a tope", *(int *)tope == 44);
    tope = pila_desapilar(pila);
    print_test("Pila desapilar pila igual a tope", *(int *)tope == 33);

    pila_destruir(pila);
    // printf("%ld\n", sizeof(pila));
    // print_test("la pila fue destruida", sizeof(pila));
}

void pruebas_pila_alumno()
{
    pruebas_pila_crear();
    pruebas_pila_destruir();
}
