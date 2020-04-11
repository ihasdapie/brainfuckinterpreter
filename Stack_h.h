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

void push_Stack(struct nodeStack** rootptrptr, int val);

int pop_Stack(struct nodeStack** rootptrptr);
//return value is set to -1 in case of empty stack: for use with positive integers only
void free_Stack(struct nodeStack** rootptr);

void disp_Stack(struct nodeStack* rootptr, int count);

struct nodeStack* new_nodeStack(int val);


