/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "bid_stack.h"
#include "product_list.h"

#define MAX_BUFFER 255





void new(char *productId, char *userId, char *productCategory, float productPrice, tList *L) {
    tItemL productData;

    productData.bidCounter = 0;
    createEmptyStack(&productData.bidStack);

    //copiamos los elementos que va a tener la lista
    strcpy(productData.productId, productId);
    strcpy(productData.seller, userId);
    productData.productPrice = productPrice;

    //seleccionamos la categoria que queremos
    if (strcmp(productCategory, "book") == 0)
        productData.productCategory = book;
    else productData.productCategory = painting;

    if (findItem(productData.productId, *L) == LNULL) {     //buscamos el primer elem de la lista
        if (insertItem(productData, L))                     //insertar elementos en la lista
            printf("* New: product %s seller %s category %s price %0.2f\n", productId, userId, productCategory,
                   productPrice);
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
        //eliminar pila(&aux.bidStack);
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

    tPosL p = findItem(productId, *L);
    tItemL aux;
    if (p == LNULL){
        printf("+ Error: Bid not possible\n");
        return;
    }
    aux = getItem(p, L);

    if(strcmp(aux.seller, userId) == 0 || aux.productPrice >= productPrice) //precio pujado mayor al precio inicial
        printf("+ Error: Bid not possible\n");

    else{
        aux.productPrice = productPrice;
        aux.bidCounter = aux.bidCounter+1;

        printf("* Bid: product %s seller %s ", productId, aux.seller);

        if(aux.productCategory == painting)
            printf("category %s ", "painting");
        else printf("category %s ", "book");

        printf("price %0.2f bids %d\n", productPrice, aux.bidCounter);

        updateItem(aux, p, L);
    }
}

void stats(tList list){
    tPosL p;
    tItemL aux;

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
        aux= getItem(p, &list);
        printf("Product %s seller %s ", aux.productId, aux.seller);

        if(aux.productCategory==book){          //si categoria es libro
            bookCont++;                         //contador suma 1
            bookSumPrice+=aux.productPrice;     //suma el precio del producto

            printf("category %s ", "book");

        }else{
            paintingCont++;
            paintSumPrice+=aux.productPrice;

            printf("category %s ", "painting");
        }

        printf("price %0.2f bids %d\n", aux.productPrice, aux.bidCounter);
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
}

void award(char *productId){

}
void withdraw(char *productId, char *userId){

}
void remove(tList list){

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

            break;
        case 'W':

            break;
        case 'R':

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

            processCommand(commandNumber, command[0], param1, param2, param3, param4);
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






