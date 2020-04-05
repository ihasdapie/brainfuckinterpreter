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
 
 
bool checkFile(FILE* file){
	//~ if file is not empty, return true
	if (file == NULL){
		return false;
	}
	else{
		return true
		}
	}

//~ void displayStatus();
//~ what possible errors are there? 1. empty file, 2. format? We can't really look at syntax in the lexer

bool lexer(FILE* input_file, FILE* output_file){
	
	const char* tokens[] = {"t_shift_right", "t_shift_left", "t_increment",
							"t_decrement", "t_output", "t_input", 
							"t_open_loop", "t_close_loop"};
	
	if (checkFile(input_file) == false){
		return false;
	}
	
	
	
	
	
	
	fclose(input_file);
	fclose(output_file);
	
}

int main(int argc, char* [argv]){
	
	bool status = lexer(fopen(argv[0], "r"), fopen(argv[1], "w"));
	if (status == false){
		printf("Error: Empty Input");
	}
	else{
		printf("Success!");
	}
	
	return 0;
}

