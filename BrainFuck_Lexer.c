/* A BrainFuck Lexer
 * Brian Chen | 2020
 * 
 * input: untokenized brainfuck
 * output: tokenized brainfuck
 * 
 *  
 * Usage: BrainFuck_Lexer <example.bf> <output.bf>
 * 
 * token format:
 * 
 * >	t_shift_right
 * <	t_shift_left
 * +	t_increment
 * -	t_decrement
 * .	t_output
 * ,	t_input
 * [	t_open_loop
 * ]	t_close_loop
 * 
 */
 
#define bool int
#define true 1
#define false 0
#include "hashmap.h"

bool checkFile(FILE* file){
	//~ if file is not empty, return true
	if (file == NULL){
		return false;
	}
	else{
		return true;
		}
	}

//~ void displayStatus();
//~ what possible errors are there? 1. empty file, 2. format? We can't really look at syntax in the lexer

bool lexer(struct hash_table* tokenTable, FILE* input_file, FILE* output_file){
    char c = 'c';

	if (checkFile(input_file) == false){
		return false;
	}
    else{
        do{
            char c = fgetc(input_file);
            const char* out_string = getValue(tokenTable, &c);
            
            if (out_string == NULL){
                continue;
            }
            
            else{
                fputs(out_string, output_file);
            }
       } while (c != EOF);
        return true;
    }
}

int main(int argc, char* argv[]){

    struct hash_table* tokenTable = createHashTable(8);
    insertEntry(tokenTable, ">", "t_shift_right\n");
    insertEntry(tokenTable, "<", "t_shift_left\n");
    insertEntry(tokenTable, "+", "t_increment\n");
    insertEntry(tokenTable, "-", "t_decrement\n");
    insertEntry(tokenTable, ".", "t_output\n");
    insertEntry(tokenTable, ",", "t_input\n");
    insertEntry(tokenTable, "[", "t_open_loop\n");
    insertEntry(tokenTable, "]", "t_close_loop\n");

    FILE* input_file = fopen(argv[0], "r");
    FILE* output_file = fopen(argv[1], "w");

	bool status = lexer(tokenTable, input_file, output_file);
	
            if (status == false){
		printf("Error: Empty Input");
	}
	else{
		printf("Success!");
	}

    fclose(input_file);
    fclose(output_file);

	return 0;
}

