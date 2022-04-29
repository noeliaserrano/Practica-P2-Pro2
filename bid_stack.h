/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Noelia Serrano Abraldes       LOGIN 1: noelia.serrano
 * AUTHOR 2: Pedro Chan Piñeiro            LOGIN 2: pedro.chan.pineiro
 * GROUP: 1.3
 * DATE: 29 / 04 / 22
 */

#ifndef BID_STACK_H
#define BID_STACK_H

#include "types.h"
#include <stdbool.h>

#define SNULL -1
#define SMAX 25

typedef int tPosS;

typedef struct tItemS {
    tUserId bidder;
    tProductPrice productPrice;
} tItemS;

typedef struct stack{
    tItemS data[SMAX];
    int top;
}tStack;

/*{ Objetivo: Creamos tStack vacía
    Salida: tStack vacía
    PostCD: tStack no tiene ningun elemento}*/
void createEmptyStack(tStack *stack);

/* { Objetivo: Mete un elemento en tStack quedando en la cima
 *   Entrada:
 *      tItemS: contenido del elemento a insertar
 *      tStack: pila donde vamos a insertar
 *   Salida:
 *      tStack: pila con tItem en la cima, true si se ha podido insertar, false en caso contrario }
 * */
bool push(tItemS d, tStack *stack);

/* { Objetivo: elimina de tStack la puja situada en la cima.
 *   Entrada:
 *      tStack: pila donde vamos a eliminar
 *   Salida:
 *      tStack: pila sin la puja en la cima
 *   PreCD: tStack no esta vacia.
 * */
void pop(tStack *stack);

/* { Objetivo: recupera el contenido de la puja situada en la cima, sin eliminarlo
 *   Entrada:
 *      tStack: pila donde obtener el dato
 *   Salida:
 *      tItemS: contenido de la puja de la cima de tStack
 *   PreCD: tStack no esta vacia
 * */
tItemS peek(tStack stack);

/* { Objetivo: determina si tStack esta vacía
 *   Entrada:
 *      la pila a comprobar (tStack)
 *   Salida:
 *      true si tStack esta vacía, falso en caso contrario
 * */
bool isEmptyStack(tStack stack);

#endif
