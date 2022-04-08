/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "types.h"
#include <stdbool.h>
#include <stdlib.h>
#include "bid_stack.h"

#define LNULL NULL

typedef struct tNode* tPosL;

typedef struct tItemL {
    tUserId seller;
    tProductId productId;
    tProductCategory productCategory;
    tProductPrice productPrice;
    tBidCounter bidCounter;
    tStack bidStack;
} tItemL;

struct tNode {
    tItemL product;
    tPosL next;
};

typedef tPosL tList;

void createEmptyList (tList*);
/* Objetivo: Crea una lista vacía.
 * Salida: Una lista vacia
 * PostCD: La lista queda inicializada y no contiene elementos. */

bool isEmptyList (tList);
/* Objetivo: Determina si la lista esta
 * Entrada: tList lista a comprobar
 * Salida: si la lista esta vacia verdadero, si no falso*/

tPosL first (tList);
/* Objetivo: Devuelve la posición del primer elemento de la lista.
 * Entrada: tList lista a modificar
 * Salida: la posicion del primer elemento
 * PreCD: La lista no está vacía.*/

tPosL last (tList);
/* Objetivo: Devuelve la posición del último elemento de la lista.
 * Entrada: tList lista a manipular
 * Salida: posicion del ultimo elemento
 * PreCD: La lista no está vacía.*/

tPosL next (tPosL, tList);
/* Objetivo: Devuelve la posición en la lista del elemento siguiente al de la posición indicada (o
 * LNULL si la posición no tiene siguiente).
 * Entrada: tPosL: posición actual del elemento
 *          tList: lista a modificar
 * PreCD: La posición indicada es una posición válida en la lista.*/

tPosL previous (tPosL, tList);
/* Objetivo: Devuelve la posición en la lista del elemento anterior al de la posición indicada (o
 * LNULL si la posición no tiene anterior).
 * Entrada: tPosL: Posicíon actual del elemento
 *          tList: Lista a manipular
 * Salida: Posicion del elemento anterior, o nulo si es el primero
 * PreCD: La posición indicada es una posición válida en la lista.*/

tPosL findPosition(tItemL d, tList L);

bool insertItem (tItemL, tList*);
/* Objetivo: Inserta un elemento en la lista antes de la posición indicada. Si la posición es LNULL,
 * entonces se añade al final. Devuelve un valor true si el elemento fue insertado; false en caso contrario.
 * Entrada: tItemL: contenido del elemento que hay que insertar
 *          tPosL: posicion de referencia
 *          tList: lista donde hay qur insertar
 * Salida: tList con el elemento tItem insertado y verdadero si se ha insertado, falso si no.
 * PreCD: La posición indicada es una posición válida en la lista o bien nula (LNULL).
 * PostCD: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado.*/

void deleteAtPosition (tPosL, tList*);
/* Objetivo: Elimina de la lista el elemento que ocupa la posición indicada.
 * Entrada: tPosL: Posicion del elemento que hay que eliminar
 *          tList: lista a modificar
 * Salida: tList: lista sin el elemento que corresponde a tPosL
 * PreCD: La posición indicada es una posición válida en la lista.
 * PostCD: Las posiciones de los elementos de la lista posteriores a la de la
 * posición eliminada pueden haber variado.*/

tItemL getItem(tPosL, tList);
/* Objetivo: Devuelve el contenido del elemento de la lista que ocupa la posición indicada.
 * Entrada: tPosL: posicion del elemento buscado
 *          tList: lista donde buscar
 * Salida: Item: contenido del elemento que esta en la posicion
 * PreCD: La posición indicada es una posición válida en la lista.*/

void updateItem (tItemL, tPosL, tList*);
/* Objetivo: Modifica el contenido del elemento situado en la posición indicada.
 * Entrada: tItemL: nuevo contenido para el elemto en tPosL
 *          tPosL: posicion del elemento que queremos actualizar
 *          tList: lista a actualizar
 * Salida: tList: lista con el contenido del elemento actualizado
 * PreCD: La posición indicada es una posición válida en la lista.
 * PostCD: El orden de los elementos de la lista no se ve modificado.*/

tPosL findItem (tProductId, tList);
/* Objetivo: Devuelve la posición del primer elemento de la lista cuyo identificador de
 * producto se corresponda con el indicado (o LNULL si no existe tal elemento).
 * Entrada: tProductId: identificador del producto buscado
 *          tList: lista donde buscar el producto
 * Salida: posicion del producto encontrado o nulo si no se encuentra. */

#endif
