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
#include "vec.h"
#include "stdbool.h"


#define TAPE_SIZE 30000


struct interpreterStruct{
    int ip; //instruction pointer
    int dp; //data pointer
    struct nodeStack* loopStack;
};

void shift_right(struct interpreterStruct* interpreter){
    if (interpreter->dp == TAPE_SIZE-1){
        printf("TAPE OUT OF BOUNDS ERROR\n");
        exit(1);
    }
    else{
        interpreter->ip++;
        interpreter->dp++;
        return;
    }

}

void shift_left(struct interpreterStruct* interpreter){
    if (interpreter->dp == 0){
        printf("TAPE OUT OF BOUNDS ERROR\n");
        exit(1);
    }
    else{
        interpreter->ip++;
        interpreter->dp--;
        return;
    }
}

void increment(struct interpreterStruct* interpreter, int tape[]){
    tape[interpreter->dp]++;
    return;
}

void decrement(struct interpreterStruct* interpreter, int tape[]){
    tape[interpreter->dp]--;
    //There is chance of int overflow...but no point catching that
    return;
}

void take_input(struct interpreterStruct* interpreter, int tape[]){
    char line[256];
    if (fgets(line, sizeof line, stdin) == NULL){
        printf("Input Error!\n");
        exit(1);
    }
    else{
        tape[interpreter->dp] = line[0];
        interpreter->ip++;
    }
    
}
void output(struct interpreterStruct* interpreter, int tape[]){
    printf("%c", tape[interpreter->dp]);
    interpreter->ip++;
}
void jump_back(struct interpreterStruct* interpreter, int tape[]);
    if (tape[interpreter->dp])



void set_loop(struct interpreterStruct* interpreter, int tape[]){
    //[
    if (tape[interpreter->dp]==0){
        interpreter->ip = pop_Stack(&(interpreter->loopStack));
    }
    else{
        if interpreter
    }push_Stack(&(interpreter->loopStack), 

}
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
    printf("|\n");
}

char* getCommands(FILE* input_file){
    char* commands = vector_create(); 
    char c = fgetc(input_file);
    while (c!= EOF){
        switch(c){
            case '>':
                vector_add(&commands, '>');
                break;
            case '<':
                vector_add(&commands, '<');
                break;
            case '+':
                vector_add(&commands, '+');
                break;
            case '-':
                vector_add(&commands, '-');
                break;
            case '.':
                vector_add(&commands, '.');
                break;
            case ',':
                vector_add(&commands, ',');
                break;
            case '[':
                vector_add(&commands, '[');
                break;
            case ']':
                vector_add(&commands, ']');
                break;
        }
    }
    vector_add(&commands, 'q');
    return commands;
}

void runInterpreter(char* commands, int tape[]){
    struct interpreterStruct interpreter;
    interpreter.ip = 0;
    interpreter.dp = 0;
    interpreter.loopStack = NULL;
    while(commands[interpreter.ip] != 'q'){
        disp_tape(tape, TAPE_SIZE);
        switch(commands[interpreter.ip]){
            case '>':
                shift_right(&interpreter);
                break;
            case '<':
                shift_left(&interpreter);
                break;
            case '+':
                increment(&interpreter, tape);
                break;
            case '-':
                decrement(&interpreter, tape);
                break;
            case '.':
                output(&interpreter, tape);
                break;
            case ',':
                take_input(&interpreter, tape);
                break;
            case '[':
                set_loop(&interpreter, tape);
                break;
            case ']':
                jump_back(&interpreter, tape);
                break;
        }
    }
    return;
}


int main(int argc, char* argv[]){

    char runMode; //'f': with file, 'l':live, 'x', error/exit
    if (argc > 2){
        printf("Too many arguments!\n");
        runMode='x';
    }
    else if (argc < 2){
        printf("Starting Live Mode\n");
        runMode='l';
    }
    else if (argc == 2){ 
        if ((strcmp(argv[1], "--h") == 0) || (strcmp(argv[1], "--help") == 0)){
            printf("Usage:\nOutput to terminal: ./interpreter <input.bf>\nLive interpreter: ./interpreter\n");
            runMode='x';
        }   
        else{
            runMode = 'f';
        }
    }


    if (runMode == 'x'){
        exit(1);
    }
    else if (runMode == 'f'){
        int tape[TAPE_SIZE] = {0}; //"standard tape size is 30,000 ints"
        FILE* input_file = fopen(argv[1], "r");
        char* commands = getCommands(input_file);
        runInterpreter(commands, tape);
    }
    else if (runMode == 'l'){
        printf("implement pls");
    }

    else{
        exit(1); //unknown option/error
    }
    
    return 0;
}
