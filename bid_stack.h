/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: 08 / 04 / 22
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

void createEmptyStack(tStack *stack);

bool push(tItemS d, tStack *stack);

void pop(tStack *stack);

tItemS peek(tStack stack);

bool isEmptyStack(tStack stack);

#endif
