/* A BrainFuck interpreter
 *
 * Brian Chen | 2020
 *
 * A interpreter struct & accompanying functions interpret brainfuck on a tape
 * represented as an int array.
 * 
 * Usage:
 *
 * 1. file input: ./interpreter.c <input.bf>
 * 2. live, "pythonic", interpreter: ./interpreter 
 * 
 * Compilation: gcc interpreter.c Stack_h.c Stack_h.h vec.c vec.h -o -ggdb(optional) <interpreter>
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
#define CYAN_OUT "\x1B[36m"
#define RESET_OUT "\x1B[0m"


struct interpreterStruct{
    int ip; //instruction pointer
    int dp; //data pointer
    struct nodeStack* loopStack; //store [ locations
    int cjb; //current ] ip to jmp to 
    char output[256]; //this may be changed. format: [size][data][data][data]... 
};

void clearScreen(){
    printf("\e[1;1H\e[2J");
}


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
    printf("Input one char: ");
    char* status = fgets(line, sizeof(line), stdin);
    if (status == NULL){
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

void set_loop(struct interpreterStruct* interpreter, int tape[], char* commands){
    //[
    if (tape[interpreter->dp]==0){ 
        //if *dp=0, jmp to matching command after ] 
        if (interpreter->cjb == -1){
            int ind = 0;
            for (int i = interpreter->ip; i<(int)vector_size(commands); i++){
                if (commands[i] == ']'){
                    ind=i;
                }
            }
            interpreter->ip=(ind+1);
        }
        else{
        }interpreter->ip = ((interpreter->cjb) + 1);
    }
    else{
        stack_Push(&interpreter->loopStack, interpreter->ip);
        interpreter->ip++;
    }
}

void disp_tape(int tape[], int* tape_size, char commands[], struct interpreterStruct interpreter){
    clearScreen();
    if (*tape_size < 10){
        *tape_size = 10;
    }
    else{
        if (interpreter.dp >= *tape_size){
            *tape_size = interpreter.dp;
        }
    }
    printf("-----------Tape------------\n");
    for (int i = 0; i < *tape_size+1; i++){
        if (i == interpreter.dp){
            printf("|%s%d%s",CYAN_OUT, tape[i], RESET_OUT);
        }
        else{
            printf("|%d", tape[i]);
            
        }
    }
    printf("|\n-----------Tape------------\n");

    printf("--------Interpreter--------\nData Pointer: %d | Instruction Pointer: %d\nAll Commands: %s\nCurrent Instruction: %c\nOutput: %s\n--------Interpreter--------\n",
            interpreter.dp, interpreter.ip, commands, commands[interpreter.ip],
            (interpreter.output+1)); //increment output to not print first value 
}

void f_getCommands(char* commands[], FILE* input_file){ 
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

void in_getCommands(char* commands[], char* input){ 
    for (int i = 0; i < (int)strlen(input); i++){ 
        switch(input[i]){
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
            case 'q':
                vector_add(commands, 'q');
                return;
        }
    }
    return;
}

void f_runInterpreter(char* commands, int tape[]){
    struct interpreterStruct interpreter;
    interpreter.ip = 0;
    interpreter.dp = 0;
    interpreter.loopStack = NULL;
    interpreter.cjb = -1;
    int tape_size = 0;

    while(commands[interpreter.ip] != 'q'){
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
        disp_tape(tape, &tape_size, commands, interpreter);
    }
}

void l_runInterpreter(char* commands, int tape[], int* tape_size, struct interpreterStruct* interpreter){
    for (int i = 0; i < (int) vector_size(commands); i++){
        switch(commands[interpreter->ip]){
            case '>':
                shift_right(interpreter); 
                break;
            case '<':
                shift_left(interpreter);
                break;
            case '+':
                increment(interpreter, tape);
                break;
            case '-':
                decrement(interpreter, tape);
                break;
            case '.':
                output(interpreter, tape);
                break;
            case ',':
                take_input(interpreter, tape);
                break;
            case '[':
                set_loop(interpreter, tape);
                break;
            case ']':
                jump_back(interpreter, tape); 
                break;
            case 'q':
                vector_free(commands);
                exit(0);
                break;
        }
        disp_tape(tape, tape_size, commands, *interpreter);
    }
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
        int tape[TAPE_SIZE] = {0};
        FILE* input_file=fopen(argv[1], "r");
        char* commands = vector_create();
        f_getCommands(&commands, input_file);
        f_runInterpreter(commands, tape);
        vector_free(commands);
    }

    else if (runMode == 'l'){
        printf("Input 'q' to quit\n");
        char input[256];
        int tape[TAPE_SIZE] = {0};
        struct interpreterStruct interpreter;
        interpreter.ip = 0;
        interpreter.dp = 0;
        interpreter.loopStack = NULL;
        interpreter.cjb = -1;
        int tape_size = 0;
        char* commands = vector_create();
        
        disp_tape(tape, &tape_size, commands, interpreter);

        while (true){
            printf("Input Commands: ");
            fgets(input, 256, stdin); //max input length = 256
            clearScreen();
            in_getCommands(&commands, input);
            l_runInterpreter(commands, tape, &tape_size, &interpreter);
        }
    }

    else{
        printf("EXIT DUE TO UNKNOWN ERROR");
        exit(1); //unknown option/error
    }

    return 0;
}
