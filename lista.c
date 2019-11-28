#include "lista.h"
#include <stdlib.h>
#include <stdio.h>


typedef struct nodo nodo_t;
struct nodo { 
    void* dato;
    struct nodo* siguiente;
};

struct lista {
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};

struct lista_iter {
    lista_t* lista;
    nodo_t* actual;
    nodo_t* anterior;
};
/* PRIMITIVAS DE LA LISTA */
lista_t* lista_crear(void){
    lista_t* lista = malloc(sizeof(lista_t));
    if (lista == NULL){
        return NULL;
    }
    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;
    return lista;
}

void lista_destruir(lista_t *lista, void destruir_dato(void*)){
    while (lista_esta_vacia(lista) == false){
        if (destruir_dato != NULL){
            destruir_dato(lista->primero->dato);
        }
        lista_borrar_primero(lista);
    }
    free (lista);
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->primero == NULL && lista->ultimo == NULL;
}

nodo_t* crear_nodo(void* valor) { 
    nodo_t* nodo = malloc(sizeof(nodo_t)); 
    if (!nodo) {
        return NULL; 
    }
    nodo->dato = valor; 
    nodo->siguiente = NULL; 
    return nodo; 
}


bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_t* nodo = crear_nodo(dato);
    if (nodo == NULL){
        return false;
    } 
    if(lista_esta_vacia(lista) == true){
        lista->ultimo = nodo;
    } else{
        nodo->siguiente = lista->primero;
    }
    lista->primero = nodo;
    lista->largo +=1;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodo_t* nodo = crear_nodo(dato);
    if (nodo == NULL){
        return false;
    } 
    if(lista_esta_vacia(lista) == true){
        lista->primero = nodo;
    } else{
        lista->ultimo->siguiente = nodo;
    }
    lista->ultimo = nodo;
    lista->largo +=1;
    return true;
}

void* lista_ver_primero(const lista_t *lista){
    if(lista_esta_vacia(lista) ==true){
        return NULL;
    }
    return (lista->primero->dato);
}

void *lista_ver_ultimo(const lista_t* lista){
    if(lista_esta_vacia(lista) ==true){
        return NULL;
    }
    return (lista->ultimo->dato);
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

void* lista_borrar_primero(lista_t *lista){
     if (lista_esta_vacia(lista) == true){
        return NULL;
    }
    void* dato_sacado = lista->primero->dato;
    nodo_t* nuevo_primero = lista->primero->siguiente;
    free(lista->primero);
    if (nuevo_primero == NULL){
        lista->primero = NULL;
        lista->ultimo = NULL;    
    }else {
        lista->primero = nuevo_primero;
    }
    lista->largo -= 1;
    return dato_sacado;
}


void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    nodo_t* actual = lista->primero;
    bool resultado = true;
    while (actual != NULL && resultado == true){
        resultado = visitar(actual->dato, extra);
        actual = actual->siguiente;
    }
}

lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if (iter == NULL){
        return NULL;
    }
    iter->lista = lista;
    iter->actual = lista->primero;
    iter->anterior = NULL;
    return iter;

}

bool lista_iter_avanzar(lista_iter_t *iter){
    if (iter->actual == NULL){
        return false;
    }
    iter->anterior = iter->actual;
    iter->actual = iter->actual->siguiente;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    if (iter->actual == NULL){
        return NULL;
    }
    return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    if (iter->actual == NULL){
        return true;
    }
    return false;
    
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    nodo_t* nodo = crear_nodo(dato);
    if (nodo == NULL){
        return false;
    }
    if (iter->anterior == NULL){
        iter->lista->primero = nodo;
    } else {
        iter->anterior->siguiente = nodo;
    }
    if (iter->actual == NULL){
        iter->lista->ultimo = nodo;
    }
    nodo->siguiente = iter->actual;
    iter->actual = nodo;
    iter->lista->largo +=1;
    return true; 
}
void *lista_iter_borrar(lista_iter_t *iter){
    if (iter->actual == NULL){
        return NULL;
    }
    if (iter->anterior == NULL){
        iter->lista->primero = iter->actual->siguiente;
    }else  {
        iter->anterior->siguiente = iter->actual->siguiente;
    }
    
    nodo_t* nodo_a_eliminar = iter->actual;
    void* dato_eliminado = iter->actual->dato;
    
    if (iter->actual->siguiente == NULL){
        iter->lista->ultimo = iter->anterior;
    }
    iter->actual = iter->actual->siguiente;
    iter->lista->largo -=1;
    free(nodo_a_eliminar);
    return dato_eliminado;
   
}
