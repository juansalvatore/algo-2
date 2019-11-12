#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include "testing.h"
#include "heap.h"

int comparar_int(const void *a, const void *b)
{
  if (*(int *)a == *(int *)b)
  {
    return 0;
  }
  else if (*(int *)a > *(int *)b)
  {
    return 1;
  }
  else
  {
    return -1;
  }
}

void destruir_dato(void *dato)
{
  free(dato);
}
void prueba_heap_vacio()
{

  printf("\nPRUEBAS HEAP VACIO\n");

  heap_t *heap = heap_crear(comparar_int);
  print_test("Se creo el heap", heap);
  print_test("La cantidad de elementos del heap es 0", !heap_cantidad(heap));
  print_test("El heap esta vacio", heap_esta_vacio(heap));
  print_test("Ver maximo es NULL", !heap_ver_max(heap));
  print_test("Desencolar en heap vacio devuelve NULL", !heap_desencolar(heap));

  heap_destruir(heap, NULL);
  print_test("Se destruyo el heap", true);
}
void prueba_un_elemento()
{
  heap_t *heap = heap_crear(comparar_int);
  int num = 10;

  printf("\nPRUEBAS HEAP UN ELEMENTO\n");
  //Pruebas con int
  print_test("Se creo el heap", heap);
  print_test("La cantidad de elementos del heap es 0", !heap_cantidad(heap));
  print_test("El heap esta vacio", heap_esta_vacio(heap));
  print_test("Encolar int", heap_encolar(heap, &num) == true);
  print_test("Ver max", heap_ver_max(heap) == &num);
  print_test("Heap esta vacia?", heap_esta_vacio(heap) == false);
  print_test("Desencolar int", heap_desencolar(heap) == &num);
  print_test("El heap esta vacio", heap_esta_vacio(heap));
  //Pruebas con NULL
  print_test("Encolar NULL", heap_encolar(heap, NULL) == false);
  print_test("Ver max", heap_ver_max(heap) == NULL);
  print_test("Heap esta vacio", heap_esta_vacio(heap) == true);
  print_test("Desencolar NULL", heap_desencolar(heap) == NULL);
  //prueba destruir dato
  char *pint = malloc(sizeof(int));
  if (!pint)
  {
    heap_destruir(heap, NULL);
    return;
  }
  *pint = 'a';
  print_test("Encolar puntero a int", heap_encolar(heap, pint) == true);
  print_test("Ver max", heap_ver_max(heap) == pint);
  print_test("Heap esta vacia?", heap_esta_vacio(heap) == false);
  heap_destruir(heap, destruir_dato);
  print_test("Destruir heap con free", true);
  return;
}

void prueba_heap_varios()
{
  printf("\nPRUEBAS HEAP CON FUNCION HEAP CREAR\n");

  int v[3] = {5, 2, 8};
  heap_t *heap = heap_crear(comparar_int);

  print_test("Se creo el heap", heap);
  print_test("El heap esta vacio", heap_esta_vacio(heap));
  print_test("Se encolo el 5", heap_encolar(heap, &v[0]));
  print_test("El heap no esta vacio", !heap_esta_vacio(heap));
  print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
  print_test("El maximo es el unico elemento encolado", heap_ver_max(heap) == &v[0]);
  print_test("Se encolo el 2", heap_encolar(heap, &v[1]));
  print_test("La cantidad de elementos es 2", heap_cantidad(heap) == 2);
  print_test("Ver maximo da el elemento correcto", heap_ver_max(heap) == &v[0]);
  print_test("Se encolo el 8", heap_encolar(heap, &v[2]));
  print_test("La cantidad de elementos es 3", heap_cantidad(heap) == 3);
  print_test("Ver maximo devuelve el elemento correcto", heap_ver_max(heap) == &v[2]);
  print_test("Encolar el mismo elemento dos veces es posible", heap_encolar(heap, &v[1]));
  print_test("La cantidad de elementos es 4", heap_cantidad(heap) == 4);
  print_test("Desencolar devuelve el maximo", heap_desencolar(heap) == &v[2]);
  print_test("La cantidad de elementos es 3", heap_cantidad(heap) == 3);
  print_test("Ver maximo devuelve el elemento correcto", heap_ver_max(heap) == &v[0]);
  print_test("Desencolar devuelve el maximo", heap_desencolar(heap) == &v[0]);
  print_test("La cantidad de elementos es 2", heap_cantidad(heap) == 2);
  print_test("Ver maximo devuelve el elemento correcto", heap_ver_max(heap) == &v[1]);
  print_test("Desencolar devuelve el maximo", heap_desencolar(heap) == &v[1]);
  print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
  print_test("Ver maximo devuelve el elemento correcto", heap_ver_max(heap) == &v[1]);
  print_test("Desencolar devuelve el maximo", heap_desencolar(heap) == &v[1]);
  print_test("El heap esta vacio", heap_esta_vacio(heap));

  heap_destruir(heap, NULL);
  print_test("Se destruyo el heap", true);
}
void prueba_heap_constructor()
{
  printf("\nPRUEBAS HEAP CON FUNCION HEAP CREAR_ARR\n");

  void **array = malloc(sizeof(void **) * 11);
  if (!array)
    return;
  int *arr_aux = malloc(sizeof(int) * 11);
  if (!arr_aux)
    return;

  for (size_t i = 0; i < 11; i++)
  {
    arr_aux[i] = (int)(i);
    array[i] = (void *)&arr_aux[i];
  }

  heap_t *heap = heap_crear_arr(array, 11, comparar_int);

  print_test("Se creo el heap", heap);
  print_test("El heap esta vacio?", !heap_esta_vacio(heap));
  print_test("Ver maximo devuelve el elemento correcto", *(int *)heap_ver_max(heap) == 10);
  print_test("La cantidad de elementos es 10", heap_cantidad(heap) == 11);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 10);
  print_test("Ver maximo devuelve el elemento correcto", *(int *)heap_ver_max(heap) == 9);
  print_test("La cantidad de elementos es 10", heap_cantidad(heap) == 10);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 9);
  print_test("Ver maximo devuelve el elemento correcto", *(int *)heap_ver_max(heap) == 8);
  print_test("La cantidad de elementos es 9", heap_cantidad(heap) == 9);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 8);
  print_test("Ver maximo devuelve el elemento correcto", *(int *)heap_ver_max(heap) == 7);
  print_test("La cantidad de elementos es 8", heap_cantidad(heap) == 8);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 7);
  print_test("Ver maximo devuelve el elemento correcto", *(int *)heap_ver_max(heap) == 6);
  print_test("La cantidad de elementos es 7", heap_cantidad(heap) == 7);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 6);
  print_test("Ver maximo devuelve el elemento correcto", *(int *)heap_ver_max(heap) == 5);
  print_test("La cantidad de elementos es 6", heap_cantidad(heap) == 6);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 5);
  print_test("Ver maximo devuelve el elemento correcto", *(int *)heap_ver_max(heap) == 4);
  print_test("La cantidad de elementos es 5", heap_cantidad(heap) == 5);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 4);
  print_test("Ver maximo devuelve el elemento correcto", *(int *)heap_ver_max(heap) == 3);
  print_test("La cantidad de elementos es 4", heap_cantidad(heap) == 4);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 3);
  print_test("Ver maximo devuelve el elemento correcto", *(int *)heap_ver_max(heap) == 2);
  print_test("La cantidad de elementos es 3", heap_cantidad(heap) == 3);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 2);
  print_test("Ver maximo devuelve el elemento correcto", *(int *)heap_ver_max(heap) == 1);
  print_test("La cantidad de elementos es 2", heap_cantidad(heap) == 2);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 1);
  print_test("Ver maximo devuelve el elemento correcto", *(int *)heap_ver_max(heap) == 0);
  print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 0);
  print_test("El heap esta vacio", heap_esta_vacio(heap));

  heap_destruir(heap, NULL);
  free(arr_aux);
  free(array);
  print_test("Se destruyo el heap", true);
}

void prueba_volumen()
{
  printf("\nPRUEBAS HEAP VOLUMEN\n");
  size_t length = 5000;
  int *arr_aux = malloc(sizeof(int) * length);
  if (!arr_aux)
    return;
  void **array = malloc(sizeof(void **) * length);
  if (!array)
    return;
  int max = 0;
  bool status = true;
  heap_t *heap = heap_crear(comparar_int);
  if (!heap)
    return;

  srand((unsigned int)time(0));
  for (int i = 0; i < (length - 1); i++)
  {
    arr_aux[i] = rand() % 1000;
    if (max < arr_aux[i])
      max = arr_aux[i];

    if (i == length / 2)
    {
      arr_aux[i] = 1200;
    }

    if (!heap_encolar(heap, &arr_aux[i]))
    {
      status = false;
      break;
    }
    array[i] = (void *)&arr_aux[i];
  }
  arr_aux[length - 1] = 1100;
  array[length - 1] = (void *)&arr_aux[length - 1];

  if (!heap_encolar(heap, &arr_aux[length - 1]))
  {
    status = false;
  }
  print_test("Se encolaron 5000 numeros random", status);
  if (!status)
    return;

  print_test("El heap esta vacio", !heap_esta_vacio(heap));
  print_test("La cantidad de elementos es 5000", heap_cantidad(heap) == length);
  print_test("Verificar maximo", *(int *)heap_ver_max(heap) == 1200);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 1200);
  print_test("Verificar maximo", *(int *)heap_ver_max(heap) == 1100);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 1100);
  print_test("Verificar maximo", *(int *)heap_ver_max(heap) == max);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == max);
  print_test("La cantidad de elementos es 5000", heap_cantidad(heap) == length - 3);

  heap_destruir(heap, NULL);

  print_test("Se destruyo el heap", true);

  heap = heap_crear_arr(array, length, comparar_int);

  print_test("Se creo el heap con arreglo", heap);
  print_test("El heap esta vacio?", !heap_esta_vacio(heap));
  print_test("La cantidad de elementos es 5000", heap_cantidad(heap) == length);
  print_test("Verificar maximo", *(int *)heap_ver_max(heap) == 1200);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 1200);
  print_test("Verificar maximo", *(int *)heap_ver_max(heap) == 1100);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == 1100);
  print_test("Verificar maximo", *(int *)heap_ver_max(heap) == max);
  print_test("Desencolar devuelve el maximo", *(int *)heap_desencolar(heap) == max);
  print_test("La cantidad de elementos es 5000", heap_cantidad(heap) == length - 3);

  heap_destruir(heap, NULL);
  free(arr_aux);
  free(array);
  print_test("Se destruyo el heap", true);
}

void pruebas_heapsort()
{
  printf("\nPRUEBA HEAPSORT\n");
  void **array = malloc(sizeof(void **) * 5);
  if (!array)
    return;
  int *arr_aux = malloc(sizeof(int) * 5);
  if (!arr_aux)
    return;
  arr_aux[0] = 4;
  arr_aux[1] = 10;
  arr_aux[2] = 1;
  arr_aux[3] = 90;
  arr_aux[4] = 0;

  for (size_t i = 0; i < 5; i++)
  {
    array[i] = (void *)&arr_aux[i];
  }
  heap_sort(array, 5, comparar_int);
  bool ok = true;
  int i;
  for (i = 0; i < 5; i++)
  {
    if (i == 0)
      continue;
    if (*(int *)array[i] < *(int *)array[i - 1])
    {
      ok = false;
      break;
    }
  }
  print_test("Ordenar con heapsort dio el resultado correcto", ok);
  free(array);
  free(arr_aux);
}

void pruebas_heap_alumno(void)
{
  prueba_heap_vacio();
  prueba_un_elemento();
  prueba_heap_varios();
  prueba_heap_constructor();
  prueba_volumen();
  pruebas_heapsort();
}