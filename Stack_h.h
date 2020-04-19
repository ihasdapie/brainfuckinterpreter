/* A linked-list stack data structure
 * 
 * Brian Chen | 2020
 * 
 * 
 *
 */
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>


struct nodeStack{
    int val;
    struct nodeStack* next;
};

struct nodeStack* new_nodeStack(int val);

void stack_Push(struct nodeStack** rootptrptr, int val);

int stack_Pop(struct nodeStack** rootptrptr);
//return value is set to -1 in case of empty stack: for use with positive integers only
void stack_Free(struct nodeStack** rootptr);

void stack_Disp(struct nodeStack* rootptr, int count);

int stack_GetTop(struct nodeStack* rootptr);
