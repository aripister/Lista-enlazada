#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct lista;
typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void*));

// Devuelve verdadero si la lista no tiene elementos, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento primero a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento primero a la lista, dato se encuentra al principio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento ultimo a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento ultimo a la lista, dato se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

//Devuelve el tamaño de la lista
//Pre: la lista fue creada
//Post: se devolvio el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void* lista_borrar_primero(lista_t *lista);

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

//Recorre la lista y aplica la funcion visitar a todo elemento de la lista
//pre: la lista fue creada
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

//Crea un iterador externo de la lista, en caso de error devuelve NULL.
//Pre: la lista fue creada
//Post: devuelve un nuevo iterador
lista_iter_t *lista_iter_crear(lista_t *lista);

//El iterador avanza, de ser posible, al elemento siguiente de la lista. En caso de error devuelve false.
//Pre: el iterador fue creado.
//Post: avanza al siguiente elemento de la lista
bool lista_iter_avanzar(lista_iter_t *iter);

//devuelve el dato del elemento sobre el que esta el iterador. en caso de error devuelve null.
//pre: el iterador fue creado.
//post: se devuelve el dato del elemento sobre el que esta el iterador, o null en caso de error.
void *lista_iter_ver_actual(const lista_iter_t *iter);

//devuelve true en caso de que el iterador este al final de la lista. en caso distinto false.
//pre: el iterador fue creado
//post: devuelve si el iterador se encuentra al final de la lista.
bool lista_iter_al_final(const lista_iter_t *iter);

//destruye el iterador externo. mantiene la lista igual.
//pre: el iterador fue creado.
void lista_iter_destruir(lista_iter_t *iter);

//inserta un elemento en la lista. en caso de error devuelve false
//pre: el iterador fue creado
//post: se agrego un nuevo elemento a la lista en la posicion del iterador. 
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//elimina un elemento de la lista.
//pre: el iterador fue creado.
void *lista_iter_borrar(lista_iter_t *iter);
/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_alumno(void);

#endif // LISTA_H