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

struct nodeStack* new_nodeStack(int val){
    struct nodeStack* newNode = (struct nodeStack*)malloc(sizeof(struct nodeStack*));
    if (newNode == 0){
        printf("-----------------------------ERROR: OUT OF MEMORY-------------------------\n");
        return NULL;
    }
    else{
        newNode->val = val;
        newNode->next = NULL;
        return newNode;
    }
}

void push_Stack(struct nodeStack** rootptrptr, int val){
    if (*rootptrptr == NULL){
        *rootptrptr = new_nodeStack(val);
        return;
    }
    else{
        struct nodeStack* temp = new_nodeStack(val);
        temp->next = *rootptrptr;
        *rootptrptr = temp;
        return;
    }
}
int pop_Stack(struct nodeStack** rootptrptr){
    if (*rootptrptr == NULL){
        return -1;
    }
    else{
        struct nodeStack* temp = (*rootptrptr);
        int retval = temp->val;
        *rootptrptr = temp->next;
        free(temp);
        temp = NULL;
        return retval;
    }
}
void free_Stack(struct nodeStack** rootptrptr){
    if ((*rootptrptr) == NULL){
        free((*rootptrptr));
    }
    else{
        free_Stack(&(*rootptrptr)->next);
        free((*rootptrptr));
        (*rootptrptr) = NULL;
        return;
    }
}
void disp_Stack(struct nodeStack* rootptr, int count){
    if (rootptr == NULL){
        //printf("-------------------------No Values Left!-------------------------\n");
        return;
    }
    else{
        printf("Value #%d: %d\n",count, rootptr->val);
        disp_Stack(rootptr->next, ++count);
        return;
    }
}


