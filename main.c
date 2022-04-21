/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Noelia Serrano Abraldes       LOGIN 1: noelia.serrano
 * AUTHOR 2: Pedro Chan Piñeiro            LOGIN 2: pedro.chan.pineiro
 * GROUP: 1.3
 * DATE: 22 / 04 / 22
 */

///
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

/*void delete(char *productId, tList *L){
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

}*/

void bid(char *productId, char *userId, float productPrice, tList* L) {

    tPosL p = findItem(productId, *L);
    tItemL aux;
    tItemS elemento;
    if (p == LNULL){
        printf("+ Error: Bid not possible\n");
        return;
    }
    aux = getItem(p, L);

    if(strcmp(aux.seller, userId) == 0 || aux.productPrice >= productPrice || aux.bidStack.top == SMAX-1)
        printf("+ Error: Bid not possible\n");

    else{
        strcpy(elemento.bidder, userId);
        elemento.productPrice=productPrice;
        //aux.productPrice = productPrice;
        aux.bidCounter = aux.bidCounter+1;

        printf("* Bid: product %s seller %s ", productId, aux.seller);

        if(aux.productCategory == painting)
            printf("category %s ", "painting");
        else printf("category %s ", "book");

        printf("price %0.2f bids %d\n", productPrice, aux.bidCounter);

        push(elemento,&aux.bidStack);
        updateItem(aux, p, L);
    }
}

void stats(tList list){
    tPosL p;
<<<<<<< HEAD
    tItemL aux, aux2;
    tItemS a;
    float b = 0;
    float c = 0;
=======
    tItemL aux;
    tItemL aux2;

    createEmptyStack(&aux2.bidStack);
>>>>>>> origin/master

    int bookCont = 0;           //contador de libros
    float bookSumPrice = 0;     //suma el precio de los libros
    float bookMediaPrice;       //media de los precios

    int paintingCont = 0;       //contador de pinturas
    float paintSumPrice = 0;    //suma el precio de las pinturas
    float paintMediaPrice;      //media de los precios

    float incremento;
    float precio;

    if(isEmptyList(list)){
        printf("+ Error: Stats not possible\n");
        return;
    }

    for (p=first(list); p!=LNULL; p=next(p, list)) {
        aux= getItem(p, list);

        if(!isEmptyStack(aux.bidStack))
            precio = aux.bidStack.data[aux.bidStack.top].productPrice;
        else
            precio = aux.productPrice;

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

<<<<<<< HEAD
        printf("price %0.2f bids %d\n", aux.productPrice, aux.bidCounter);

        ///
        a = peek(aux.bidStack);
        b = ( (a.productPrice - aux.productPrice) / aux.productPrice ) * 100;

        if (c < b) {
            c = b;
            aux2 = aux;
        }
        ///

=======
        if(isEmptyStack(aux.bidStack))
            printf("price %0.2f. No bids\n", aux.productPrice);
        else
            printf("price %0.2f bids %d top bidder %s\n",
                   precio, aux.bidCounter, aux.bidStack.data[aux.bidStack.top].bidder);

            if(isEmptyStack(aux2.bidStack)){
                aux2=aux;
            }
            if(aux.bidStack.data[aux.bidStack.top].productPrice>aux2.bidStack.data[aux2.bidStack.top].productPrice)
                aux2=aux;
>>>>>>> origin/master
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
<<<<<<< HEAD
    ///
    if(c != 0){
        printf("Top bid: Product %s seller %s category %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
               aux2.productId, aux2.seller, aux2.productCategory == painting? "painting": "book", aux2.productPrice,
               a.bidder, a.productPrice, c);
    } else {
        printf("Top bid: not possible\n");
    }
    ///
=======


    //pila de pujas

    if(isEmptyStack(aux2.bidStack))
        printf("Top bid not possible\n");

    else{
        printf("Top bid: Product %s seller %s ", aux2.productId, aux2.seller);
        if(aux2.productCategory == painting)
            printf("category %s ", "painting");
        else printf("category %s ", "book");

        printf("price %0.2f bidder %s top price %0.2f ", aux2.productPrice, aux2.bidStack.data[aux2.bidStack.top].bidder, aux2.bidStack.data[aux2.bidStack.top].productPrice);
        incremento = (aux2.bidStack.data[aux2.bidStack.top].productPrice - aux2.productPrice)/(aux2.productPrice);
        printf("increase %0.2f%\n", incremento*100) ;
    }
>>>>>>> origin/master
}

/*void award(char *productId){

}
void withdraw(char *productId, char *userId){

}
<<<<<<< HEAD
//void remove(tList list){

//}
=======
void remove(tList list){
    tItemL aux;
    tPosL p;

    if(isEmptyStack(aux.bidStack)){
        printf("+ Error: remove nor possible\n");
    }
}*/
>>>>>>> origin/master


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
        /*case 'D':
            printf("********************\n");
            printf("%s %c: product %s\n", commandNumber, command, param1);
            delete(param1, L);
            break;
        case 'A':
            printf("********************\n");
            break;
        case 'W':
            printf("********************\n");
            break;
        case 'R':
            printf("********************\n");
            break;*/
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






