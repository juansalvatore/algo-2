#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct hash hash_t;
typedef struct hash_iter hash_iter_t;

// tipo de funcion para destruir dato
typedef void (*hash_destruir_dato_t)(void *);

// HASH

// Crea el hash.
// Post: devuelve una nuevo hash vacío.
hash_t *hash_crear(hash_destruir_dato_t destruir_dato);

// Inserta un elemento en el hash, si la clave ya existe la reemplaza.
// En caso de error devuelve false.
// Pre: el hash fue inicializado.
// Post: se almaceno la clave y el dato correspondientes.
bool hash_guardar(hash_t *hash, const char *clave, void *dato);

// Borra un elemento del hash y devuelve el dato correspondiente a la clave.
// Si el dato no existia devuelve NULL.
// Pre: el hash fue inicializado.
// Post: se eliminó el elemento y se retorno el dato si existia previamente.
void *hash_borrar(hash_t *hash, const char *clave);

// Retorna el dato correspondiente a la clave pasada como segundo argumento.
// En caso de no existir la clave devuelve NULL.
// Pre: el hash fue inicializado.
// Post: retorna el dato correspondiente a la clave.
void *hash_obtener(const hash_t *hash, const char *clave);

// Devuelve true si la clave pertenece al hash y false si no se encuentra.
// Pre: el hash fue inicializado.
// Post: retorna el valor true o false dependiendo de si existe la clave.
bool hash_pertenece(const hash_t *hash, const char *clave);

// Devuelve la cantidad de elementos del hash.
// Pre: el hash fue inicializado.
// Post: retorna la cantidad de elementos guardados en el hash.
size_t hash_cantidad(const hash_t *hash);

// Destruye el tda liberando la memoriay ejecutando la funcion destruir
// para cada clave y valor.
// Pre: el hash fue inicializado.
// Post: el hash fue destruido.
void hash_destruir(hash_t *hash);

// ITERADOR EXTERNO

// crea el iterador externo de hash
hash_iter_t *hash_iter_crear(const hash_t *hash);
// avanza el iterador
bool hash_iter_avanzar(hash_iter_t *iter);
// retorna la clave actual
const char *hash_iter_ver_actual(const hash_iter_t *iter);
// retorna true o false dependiendo si iteró el hash por completo
bool hash_iter_al_final(const hash_iter_t *iter);
// destruye el iterador externo
void hash_iter_destruir(hash_iter_t *iter);

#endif