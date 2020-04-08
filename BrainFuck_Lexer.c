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



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


#define bool int
#define true 1
#define false 0
#define str_lngth 256

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

void lexer(const char symbols[][str_lngth], const char tokens[][str_lngth], FILE* input_file, FILE* output_file){

    char c = 75;

    if (checkFile(input_file) == false){
	    printf("bad input file\n");
        return;
	}


    else{
        while (c != EOF){
            c = fgetc(input_file);
            if (c == *symbols[0]){
                fputs(tokens[0], output_file);
            }
            else if (c == *symbols[1]){
                fputs(tokens[1], output_file);
            }
            else if (c == *symbols[2]){
                fputs(tokens[2], output_file);
            }
            else if (c == *symbols[3]){
                fputs(tokens[3], output_file);
            }
            else if (c == *symbols[4]){
                fputs(tokens[4], output_file);
            }
            else if (c == *symbols[5]){
                fputs(tokens[5], output_file);
            }
            else if (c == *symbols[6]){
                fputs(tokens[6], output_file);
            }
            else if (c == *symbols[7]){
                fputs(tokens[7], output_file);
            }
        }
    }
}


int main(int argc, char* argv[]){

    const char symbols[][str_lngth] = {">", "<", "+", "-", ".", ",", "[", "]"};
    const char tokens[][str_lngth] = {"t_shift_right\n", "t_shift_left\n", "t_increment\n", "t_decrement\n",
                                        "t_output\n", "t_input\n", "t_open_loop\n", "t_close_loop\n"};

    if (argc > 3){
        printf("Too many arguments\n");
    }

    if (argc < 3){
        printf("Please specify <input.bf> and <output.bf>\nRefer to --help for details\n");
    }

    if (argc == 2){
        if ((strcmp(argv[1], "--h") == 0) || (strcmp(argv[1], "--help") == 0)){
            printf("Usage: ./BrainFuck_Lexer <input.bf> <output.bf>\n");
        }
    } 
    
    FILE* input_file = fopen(argv[1], "r");
    FILE* output_file = fopen(argv[2], "w");

	lexer(symbols, tokens, input_file, output_file);

    /*	
    if (status == false){
		printf("Error: Empty Input");
	}
	else{
		printf("Success!");
	}

    fclose(input_file);
    fclose(output_file);
*/
	return 0;
}

