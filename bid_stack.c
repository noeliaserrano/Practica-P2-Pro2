/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "bid_stack.h"

void createEmptyStack(tStack *stack){
    stack -> top = SNULL;
}
bool push(tItemS d, tStack *stack){
    if(stack -> top == SMAX -1) //pila llena
        return false;
    else{
        stack -> top++;
        stack ->data[stack->top]=d;
        return true;
    }
}
void pop(tStack *stack){
    stack -> top--;
}
tItemS peek(tStack stack){
    return stack.data[stack.top];
}
bool isEmptyStack(tStack stack){
    return (stack.top == SNULL);
}
