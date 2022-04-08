/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Noelia Serrano Abraldes        LOGIN 1: noelia.serrano
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: 1.3
 * DATE: 08 / 04 / 22
 */
#include "types.h"
#include "product_list.h"
#include <string.h>

//PosC: L no tiene ningun dato
void createEmptyList (tList *L){
    *L = LNULL;
}

bool createNode(tPosL* p){
    *p = malloc(sizeof(struct tNode)); //reservamos espacio en memoria
    return *p != LNULL;
}

bool isEmptyList (tList L){
    return L == LNULL;
}

//PreC: lista no esta vacia
tPosL first (tList L){
    return L;
}

//PreC: lista no vacia. No hace falta comprobarlo
tPosL last (tList L){
    tPosL aux = NULL;

    if(L == LNULL)
        return LNULL;

    aux = L;
    while(aux -> next != LNULL)
        aux = next(aux, L);

    return aux;
}

// PreC: p posicion valida de la lista
tPosL next (tPosL p, tList L){
    return p -> next;
}

//PreC: p es una posicion valida de L
tPosL previous (tPosL p, tList L){
    tPosL aux = NULL;
    if(L == p)
        return LNULL;

    aux = first(L);
    while (aux ->next != p)
        aux = next(aux, L);

    return aux;
}

tPosL findPosition(tItemL d, tList L){
    tPosL p;
    p=L;
    while ((p->next != NULL) && (0 > strcmp(p->next->product.productId, d.productId)))
        p = p->next;
    return p;
}

/*Inserta un elemento en la Lista de forma ordenada por el campo productId. Devuelve
un valor true si el elemento fue insertado; false en caso contrario.
PostCD: Las posiciones de los elementos de la lista posteriores a la del
elemento insertado pueden haber variado.*/
bool insertItem (tItemL d, tList *L){
    tPosL a, b;

    if(!createNode(&a))
        return false;
    else{
        a -> product = d;
        a -> next = LNULL;

        if(*L==LNULL) {
            *L = a;
        } else if(strcmp((*L)->product.productId, d.productId)>0) {
            a -> next = *L;
            *L = a;
        } else {
            b = findPosition(d, *L);
            a -> next = b -> next;
            b -> next = a;

        }
        return true;
    }
}

/* PreC: p posicion valida de la lista y el producto tiene una pila de pujas vacia
 * PosC: las posiciones de los elementos siguientes a la del
 *       elemento de la posicion pueden estar afectados*/
void deleteAtPosition (tPosL p, tList *L){
    tPosL q;

    if(p == *L)
        *L = (*L)->next;
    else if(p->next == LNULL){
        for (q = *L; q->next != p; q = q->next);
        q->next = LNULL;
    }
    else{
        q = p->next;
        p->product = q->product;
        p->next = q->next;
        p = q;
    }
    free(p);
}

// PreC: p posicion valida de la lista
tItemL getItem(tPosL p, tList L){
    return p -> product;
}

// PreC: p posicion valida de la lista
void updateItem (tItemL d, tPosL p, tList *L){
    p->product = d;
}


tPosL findItem (tProductId t, tList L){
    tPosL p;
    if(isEmptyList(L))
        p = LNULL;
    else
        for(p = L; (p != LNULL) && (strcmp(p -> product.productId, t)); p = p -> next); //usamos strcmp para comprobar que no hay dos productos con id iguales
    return p;
}