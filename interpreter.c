/* A BrainFuck interpreter
 *
 * Brian Chen | 2020
 *
 * A interpreter struct & accompanying functions to operate on a tape
 * represented as an int array.
 * 
 * Usage:
 * 
 * 1. output to file: ./interpreter.c <input.bf> <output.bf>
 * 2. output to command line <input.bf>
 * 
 * ToDo: live visualizer-style interpreter
 *
 */



#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "Stack_h.h"

#define TAPE_SIZE 30000


struct interpreterStruct{
    int ip; //instruction pointer
    int dp; //data pointer
    struct nodeStack* loopStack;
};

void shift_right(struct interpreterStruct* interpreter, int tape[]);
void shift_left(struct interpreterStruct* interpreter, int tape[]);
void increment(struct interpreterStruct* interpreter, int tape[]);
void decrement(struct interpreterStruct* interpreter, int tape[]);
void take_input(struct interpreterStruct* interpreter, int tape[]);
void output(struct interpreterStruct* interpreter, int tape[]);
void jump_back(struct interpreterStruct* interpreter);
void set_loop(struct interpreterStruct* interpreter);
void disp_tape(int tape[], int tape_size);
void t_runInterpreter(struct interpreterStruct* interptr, int tape[], FILE* input_file);
void f_runInterpreter(struct interpreterStruct* interptr, int tape[], FILE* input_file, FILE* output_file);


int main(int argc, char* argv[]){

    char runMode = '-'; //'f': write to file, 't': output to terminal
    if (argc > 3){
        printf("Too many arguments!\n");
        return 0;
    }

    else if (argc < 2){
        printf("Please specify <input.bf>\nRefer to --help for details\n");
        return 0;
    }

    else if (argc == 2){
        if ((strcmp(argv[1], "--h") == 0) || (strcmp(argv[1], "--help") == 0)){
            printf("Usage:\nOutput to terminal: ./interpreter <input.bf>\nOutput to file: ./interpreter <input.bf> <output>\n");
        }
        else{
            runMode = 't';
        }
    }

    else{
        runMode  = 'f';
    }


//variables
    int tape[TAPE_SIZE] = {0}; //"standard tape size is 30,000 ints"
    struct interpreterStruct interpreter;
    interpreter.ip = 0;
    interpreter.dp = 0;
    interpreter.loopStack = NULL;

    if (runMode == 'f'){
        FILE* input_file = fopen(argv[1], "r");
        FILE* output_file = fopen(argv[2], "w");
        f_runInterpreter(&interpreter, tape, input_file, output_file);
    }

    else if (runMode == 't'){
        FILE* input_file = fopen(argv[1], "r");
        t_runInterpreter(&interpreter, tape, input_file);
    }

    return 0;
}



void shift_right(struct interpreterStruct* interpreter, int tape[]);
void shift_left(struct interpreterStruct* interpreter, int tape[]);
void increment(struct interpreterStruct* interpreter, int tape[]);
void decrement(struct interpreterStruct* interpreter, int tape[]);
void take_input(struct interpreterStruct* interpreter, int tape[]);
void output(struct interpreterStruct* interpreter, int tape[]);
void jump_back(struct interpreterStruct* interpreter);
void set_loop(struct interpreterStruct* interpreter);

void disp_tape(int tape[], int tape_size){
    if (tape_size < 10){
        tape_size = 10;
    }
    else{
        tape_size = tape_size + 1;
    }
    for (int i = 0; i < tape_size; i++){
        printf("|%d", tape[i]);
    } 
    printf("\n");
}


void t_runInterpreter(struct interpreterStruct* interptr, int tape[], FILE* input_file);
void f_runInterpreter(struct interpreterStruct* interptr, int tape[], FILE* input_file, FILE* output_file){
    
    int tape_size = 0;

    char c = fgetc(input_file);
    
    while (c != EOF){   
        if (c == '>'){
            shift_right(interptr, tape);
        }
        
        else if (c == '<'){
            shift_left(interptr, tape);
        }

        else if (c == '+'){
            increment(interptr, tape);
        }

        else if (c == '-'){
            decrement(interptr, tape);
        }

        else if (c == '.'){
            output(interptr, tape);
        }

        else if (c == ','){
            take_input(interptr, tape);
        }

        else if (c == '['){
            set_loop(interptr);
        }

        else if (c == ']'){
            jump_back(interptr);
        }

        if ((interptr->dp)>tape_size){
            tape_size = interptr->dp;
        }
        disp_tape(tape, tape_size);
        c = fgetc(input_file);
    }
}


