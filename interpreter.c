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
    return commands;
}

void t_runInterpreter(char* commands, int tape[]){
    struct interpreterStruct interpreter;
    interpreter.ip = 0;
    interpreter.dp = 0;
    interpreter.loopStack = NULL;


}




int main(int argc, char* argv[]){

    char runMode; //'f': write to file, 't': output to terminal
    if (argc > 3){
        printf("Too many arguments!\n");
        exit(1);
    }
    else if (argc < 2){
        printf("Please specify <input.bf>\nRefer to --help for details\n");
        exit(1);
    }
    else if (argc == 2){ 
        if ((strcmp(argv[1], "--h") == 0) || (strcmp(argv[1], "--help") == 0)){
            printf("Usage:\nOutput to terminal: ./interpreter <input.bf>\nOutput to file: ./interpreter <input.bf> <output>\n");
            exit(1);
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
       if (runMode == 't'){
        FILE* input_file = fopen(argv[1], "r");
        char* commands = getCommands(input_file);
        t_runInterpreter(tape, commands);
    }

    return 0;
}
