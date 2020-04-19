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
    struct nodeStack* loopStack; //store [ locations
    int cjb; //current ] ip to jmp to 
    char output[256]; //this may be changed. format: [size][data][data][data]... 
};

void shift_right(struct interpreterStruct* interpreter){
    if (interpreter->dp == TAPE_SIZE-1){
        printf("TAPE OUT OF BOUNDS ERROR\n");
        exit(1);
    }
    else{
        ++interpreter->ip;
        ++interpreter->dp;
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
        printf("nodte%d", interpreter->ip);
        return;
    }
}

void increment(struct interpreterStruct* interpreter, int tape[]){
    tape[interpreter->dp]++;
    interpreter->ip++;
    return;
}

void decrement(struct interpreterStruct* interpreter, int tape[]){
    tape[interpreter->dp]--;
    //There is chance of int overflow...but no point catching that
    interpreter->ip++;
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
    (interpreter->output)[0]++;
    interpreter->output[(int)interpreter->output[0]] = tape[interpreter->dp];
}

void jump_back(struct interpreterStruct* interpreter, int tape[]){
    //]
    interpreter->cjb = interpreter->ip;
    if (tape[interpreter->dp] == 0){
        interpreter->ip++;
        stack_Pop(&interpreter->loopStack);
    }
    else{
        interpreter->ip = stack_GetTop((interpreter->loopStack))+1;
    }
}

void set_loop(struct interpreterStruct* interpreter, int tape[]){
    //[
    if (tape[interpreter->dp]==0){ 
        //if *dp=0, jmp to matching command after ] 
        interpreter->ip = ((interpreter->cjb) + 1);
    }
    else{
        stack_Push(&interpreter->loopStack, interpreter->ip);
        interpreter->ip++;
    }
}




void disp_tape(int tape[], int* tape_size, char commands[], struct interpreterStruct interpreter){
    if (*tape_size < 10){
        *tape_size = 10;
    }
    else{
        if (interpreter.dp > *tape_size){
            *tape_size = interpreter.dp;
        }
    }
    
    printf("--------Interpreter--------\nDataPointer: %d\nInstructionPointer: %d\nCurrent Instruction: %c\n--------Interpreter-------\n\nOutput: %s\n", 
            interpreter.dp, interpreter.ip, commands[interpreter.ip], (interpreter.output+1)); //increment output to not print first value
    for (int i = 0; i < *tape_size; i++){
        printf("|%d", tape[i]);
    } 
    printf("|\n");
}

void getCommands(char* commands[], FILE* input_file){ 
    printf("ran getCommands\n");
    char c = fgetc(input_file);
    while (c!= EOF){
        switch(c){
            case '>':
                vector_add(commands, '>');
                break;
            case '<':
                vector_add(commands, '<');
                break;
            case '+':
                vector_add(commands, '+');
                break;
            case '-':
                vector_add(commands, '-');
                break;
            case '.':
                vector_add(commands, '.');
                break;
            case ',':
                vector_add(commands, ',');
                break;
            case '[':
                vector_add(commands, '[');
                break;
            case ']':
                vector_add(commands, ']');
                break;
        }
        c = fgetc(input_file);
    }
    vector_add(commands, 'q');
    return;
}

void runInterpreter(char* commands, int tape[]){
    struct interpreterStruct interpreter;
    interpreter.ip = 0;
    interpreter.dp = 0;
    interpreter.loopStack = NULL;
    interpreter.cjb = -1;
    int tape_size = 0;

    while(commands[interpreter.ip] != 'q'){
        disp_tape(tape, &tape_size, commands, interpreter);
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
    char runMode = -1; //'f': with file, 'l':live, 'x', error/exit
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
        printf("EXIT DUE TO RUNMODE x");
        exit(1);
    }

    else if (runMode == 'f'){
        printf("aaa");
        int tape[TAPE_SIZE] = {0};
        printf("bbb");
        FILE* input_file=fopen(argv[1], "r");
        printf("ccc");
        char* commands = vector_create();
        getCommands(&commands, input_file);
        runInterpreter(commands, tape);
        vector_free(commands);

            /*     } */
/*     else if (runMode == 'l'){ */
/*         printf("implement pls\n"); */
/*     } */

/*     else{ */
/*         printf("EXIT DUE TO UNKNOWN ERROR"); */
/*         exit(1); //unknown option/error */
/*     } */

    return 0;
    }
}
