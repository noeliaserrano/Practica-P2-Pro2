#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "bid_stack.h"
#include "product_list.h"

#define MAX_BUFFER 255

/*char *categorias(tProductCategory categoria){

    if(categoria == painting)
        printf("category %s ", "painting");
    else printf("category %s ", "book");
}*/

void new(char *productId, char *userId, char *productCategory, float productPrice, tList *L) {
/* { Objetivo: Dar de alta un nuevo producto
 *   Entrada:
 *      productId: cadena que corresponde con el id del producto
 *      userId: cadena que corresponde con el id de cada usuario
 *      productCategory: tipo enumerado, con la categoria
 *      productPrice: float con el precio de cada producto
 *   Salida:
 *      la lista con un nuevo producto, se añade en el orden correspondiente si no esta añadido previamente y una pila
 *       }
 *   PreCD: la lista esta inicializa
 *   PostCD: las posiciones de los productos pueden haber cambiado
 * */
    tItemL productData;

    productData.bidCounter = 0;
    createEmptyStack(&productData.bidStack);

    //copiamos los elementos que va a tener la lista
    strcpy(productData.productId, productId);
    strcpy(productData.seller, userId);
    productData.productPrice = productPrice;

    if (strcmp(productCategory, "book") == 0)
        productData.productCategory = book;
    else productData.productCategory = painting;

    if (findItem(productData.productId, *L) == LNULL) {     //buscamos el primer elem de la lista
        if (insertItem(productData, L))                     //insertar elementos en la lista
            printf("* New: product %s seller %s category %s price %0.2f\n", productId, userId, productCategory, productPrice);
        else{
            printf("+ Error: New not possible\n");
            return;
        }
    } else
        printf("+ Error: New not possible\n");
}

void delete(char *productId, tList *L){
    tPosL p = findItem(productId, *L);
    tItemL aux;

    if(p == LNULL)
        printf("+ Error: Delete not possible\n");
    else{
        aux = getItem(p, *L);
        pop(&aux.bidStack); //eliminar pila
        updateItem(aux, p, L);
        deleteAtPosition(p, L);

        printf("* Delete: product %s seller %s ", productId, aux.seller);

        //selecccion de categoria
        if(aux.productCategory == painting)
            printf("category %s ", "painting");
        else printf("category %s ", "book");

        printf("price %0.2f bids %d\n", aux.productPrice, aux.bidCounter);
    }

}

void bid(char *productId, char *userId, float productPrice, tList* L) {
/* { Objetivo: Pujar por un determinado producto
 *   Entrada:
 *      productId: cadena que corresponde con el id del producto
 *      userId: cadena que corresponde con el id de cada usuario
 *      productPrice: float con el precio de cada producto
 *      tList: la lista ordenada con todos los productos y sus pujas
 *   Salida:
 *      tList: la lista con una nueva puja en la pila
 *   PreCD: la lista de productos y la pila deben de estar inicializadas}
 * */
    tPosL p = findItem(productId, *L);
    tItemL aux;
    tItemS elemento;

    if (p == LNULL){
        printf("+ Error: Bid not possible\n");
        return;
    }

    aux = getItem(p, *L);
    if(strcmp(aux.seller, userId) == 0 || aux.productPrice >= productPrice || aux.bidStack.top == SMAX-1) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    else if(!isEmptyStack(aux.bidStack)){
        elemento = peek(aux.bidStack);
        if(elemento.productPrice>productPrice){
            printf("+ Error: Bid not possible\n");
            return;
        }
    }

    strcpy(elemento.bidder, userId);
    elemento.productPrice=productPrice;
    aux.bidCounter = aux.bidCounter+1;

    printf("* Bid: product %s bidder %s ", productId, elemento.bidder);

    if(aux.productCategory == painting)
        printf("category %s ", "painting");
    else printf("category %s ", "book");

    printf("price %0.2f bids  %d\n", elemento.productPrice, aux.bidCounter);

    push(elemento,&aux.bidStack);
    updateItem(aux, p, L);
}

void stats(tList list){
/* { Objetivo: Listado de los productos actuales de BIDFIC y sus datos
 *   Entrada:
 *      tList: la lista ordenada con todos los
 *      tList: la lista ordenada con todos los productos y sus pujas
 *   Salida:
 *      tList: la lista sin modificar
 *   PreCD: la lista de productos y la pila deben de estar inicializadas }
 *   */
    tPosL p;
    tItemL aux;
    tItemL aux2;
    float precio;
    float incremento;

    createEmptyStack(&aux2.bidStack);

    int bookCont = 0;           //contador de libros
    float bookSumPrice = 0;     //suma el precio de los libros
    float bookMediaPrice;       //media de los precios

    int paintingCont = 0;       //contador de pinturas
    float paintSumPrice = 0;    //suma el precio de las pinturas
    float paintMediaPrice;      //media de los precios

    if(isEmptyList(list)){
        printf("+ Error: Stats not possible\n");
        return;
    }

    for (p=first(list); p!=LNULL; p=next(p, list)) {
        aux=getItem(p, list);

        precio = aux.productPrice;
        printf("Product %s seller %s ", aux.productId, aux.seller);

        if(aux.productCategory==book){          //si categoria es libro
            bookCont++;                         //contador suma 1
            bookSumPrice+=precio;               //suma el precio del producto

            printf("category %s ", "book");

        }else{
            paintingCont++;
            paintSumPrice+=precio;

            printf("category %s ", "painting");
        }

        if(isEmptyStack(aux.bidStack))
            printf("price %0.2f. No bids\n", aux.productPrice);
        else {
            printf("price %0.2f bids %d top bidder %s\n",
                   aux.productPrice, aux.bidCounter, aux.bidStack.data[aux.bidStack.top].bidder);
            if(isEmptyStack(aux2.bidStack)){
                aux2=aux;
            }
            if(aux.bidStack.data[aux.bidStack.top].productPrice > aux2.bidStack.data[aux2.bidStack.top].productPrice)
                aux2=aux;
        }
    }

    //calculamos el precio medio
    if(bookCont==0)
        bookMediaPrice = 0;
    else
        bookMediaPrice = bookSumPrice/(float)bookCont;

    if(paintingCont==0)
        paintMediaPrice = 0;
    else
        paintMediaPrice = paintSumPrice/(float)paintingCont;

    printf("\nCategory  Products    Price  Average\n");
    printf("Book      %8d %8.2f %8.2f\n", bookCont, bookSumPrice, bookMediaPrice);
    printf("Painting  %8d %8.2f %8.2f\n", paintingCont, paintSumPrice, paintMediaPrice);

    //pila de pujas

    if(isEmptyStack(aux2.bidStack))
        printf("Top bid not possible\n");

    else{

        printf("Top bid: Product %s seller %s ", aux2.productId, aux2.seller);
        if(aux2.productCategory == painting)
            printf("category %s ", "painting");
        else printf("category %s ", "book");

        printf("price %0.2f bidder %s top price %0.2f ", aux2.productPrice, aux2.bidStack.data[aux2.bidStack.top].bidder,
               aux2.bidStack.data[aux2.bidStack.top].productPrice);
        incremento = (aux2.bidStack.data[aux2.bidStack.top].productPrice - aux2.productPrice)/(aux2.productPrice);
        printf("increase %0.2f%%\n", incremento*100) ;
    }
}

void award(char *productId, tList *L){
    tPosL p = findItem(productId, *L);
    tItemL aux;

    if (p == LNULL || isEmptyStack(aux.bidStack)){    //producto no existe o pila vacia
        printf("+ Error: Award not possible\n");
        return;
    }

}

void withdraw(char *productId, char *userId, tList *L){
    tPosL p = findItem(productId, *L);
    tItemL aux;

    if (p == LNULL || isEmptyStack(aux.bidStack) || strcmp(aux.seller, userId) != 0 ){
        printf("+ Error: Withdraw not possible\n");
        return;
    }


}

void Remove(tList *L){
    tItemL aux;
    tPosL p;

    if(isEmptyStack(aux.bidStack)){
        printf("+ Error: Remove not possible\n");
    }
}


void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *L) {

    float price;
    switch (command) {
        case 'N':
            price = atof(param4);
            printf("********************\n");
            printf("%s %c: product %s seller %s category %s price %0.2f\n", commandNumber, command, param1, param2, param3, price);
            new(param1, param2, param3, price, L);
            break;
        case 'S':
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            stats(*L);
            break;
        case 'B':
            price = atof(param3);
            printf("********************\n");
            printf("%s %c: product %s bidder %s price %0.2f\n", commandNumber, command, param1, param2, price);
            bid(param1, param2, price, L);
            break;
        case 'D':
            printf("********************\n");
            printf("%s %c: product %s\n", commandNumber, command, param1);
            delete(param1, L);
            break;
        case 'A':
            printf("********************\n");
            printf("%s %c: product %s\n", commandNumber, command, param1);
            award(param1, L);
            break;
        case 'W':
            printf("********************\n");
            printf("%s %c: product %s bidder %s\n", commandNumber, command, param1, param2);
            withdraw(param1, param2, L);
            break;
        case 'R':
            printf("********************\n");
            printf("%s %c \n", commandNumber, command);
            Remove(*L);
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    tList L;
    createEmptyList(&L);
    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4, &L);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}






