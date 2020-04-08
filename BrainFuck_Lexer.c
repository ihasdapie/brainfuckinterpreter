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
//#include "hashmap.h"

struct map_entry{
	char* key;
	char* value;
	struct map_entry* next;
};

struct hash_table{
	int size;   
	struct map_entry **table;
};

int createHash(struct hash_table* hashTable, char* key){
	unsigned long int hash = 0;
	unsigned long i = 0;
	
	while ((hash < ULONG_MAX) && (i < strlen(key))){
		hash = hash << 8;
		hash = hash + key[i];
		i++;
    }

	hash = hash % hashTable->size;
	return hash;
}

struct map_entry* createEntry(char* key, char* value){
    struct map_entry* newEntry;
	
    if ((newEntry = malloc(sizeof(struct map_entry))) == NULL){ 
        return NULL;
    }
    
    if ((newEntry->key = strdup(key)) == NULL){
        return NULL;
    }
	
    if ((newEntry->value = strdup(value))==NULL){
        return NULL;
    }

    newEntry->next = NULL;

    return newEntry;
}


void insertEntry(struct hash_table* hashTable, char* key, char* value){
    struct map_entry * next = NULL;
    struct map_entry * last = NULL;
    
    int hash = createHash(hashTable, key);
    next = hashTable->table[hash];

    while((next != NULL)&&(next->key != NULL)&&(strcmp(key, next->key)>0)){
        last = next;
        next = next -> next;
    }

    if ((next != NULL)&&(next->key != NULL)&&(strcmp(key, next->key)==0)){
    /*If key-value pair already exists, update to new value*/
        free(next->value);
        next->value = strdup(value);
    }

    else{
        /*If key-value pair does not exist, create new pair*'*/
        struct map_entry* newEntry = createEntry(key, value);
        
        if (next == hashTable->table[hash]){
            newEntry->next = next;
            hashTable->table[hash] = newEntry;
        }
        else if (next == NULL){
            last->next = newEntry;
        }
        else{
            newEntry->next = next;
            last->next = newEntry;
        }

    }
}

struct hash_table* createHashTable(int size){
	
	struct hash_table* hashTable = NULL;
	
	if (size < 1){
		return NULL;
	}
	
	if ((hashTable = malloc(sizeof(struct hash_table))) == NULL){
		return NULL;
	}
	
	if ((hashTable->table = malloc(sizeof(struct map_entry*)*size)) == NULL){
		return NULL;
	}
	
	for (int i = 0; i < size; i++){
		hashTable->table[i] = NULL;
	}

	hashTable->size = size;
	
	return hashTable;
}

char* getValue(struct hash_table* hashTable, char* key){
    unsigned long hash = createHash(hashTable, key);
    struct map_entry* entry = hashTable->table[hash];

    while ((entry == NULL)||(entry->key == NULL)||(strcmp(key,entry->key)>0)){
        //step through looking for the entry
        entry = entry->next;
    }
    


    if ((entry == NULL)||(entry->key == NULL)||(strcmp(key, entry->key)!=0)){
        return NULL;
    }

    else{
        return entry->value;
    }
}
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

void lexer(struct hash_table* tokenTable, FILE* input_file, FILE* output_file){

    printf("itried");

    char c = 75;


    if (checkFile(input_file) == false){
	    printf("bad input file\n");
        return;
	}


    else{
        while (c != EOF){
            c = fgetc(input_file);
            printf("%s", &c);
        }
    }
/*    
    else{
        printf("aaa");
        do{
            printf("a");
            c = fgetc(input_file);
            printf("b");
            char* out_string = getValue(tokenTable, &c);
            printf("c");
            if (out_string == NULL){
                continue;
            }
            
            else{
                fputs(out_string, output_file);
            }
       } while (c != EOF);
        return;
    }
*/
}


int main(int argc, char* argv[]){
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
    
    struct hash_table* tokenTable = createHashTable(9);
    
    insertEntry(tokenTable, ">", "t_shift_right\n");
    insertEntry(tokenTable, "<", "t_shift_left\n");
    insertEntry(tokenTable, "+", "t_increment\n");
    insertEntry(tokenTable, "-", "t_decrement\n");
    insertEntry(tokenTable, ".", "t_output\n");
    insertEntry(tokenTable, ",", "t_input\n");
    insertEntry(tokenTable, "[", "t_open_loop\n");
    insertEntry(tokenTable, "]", "t_close_loop\n");
   
    FILE* input_file = fopen(argv[1], "r");
    FILE* output_file = fopen(argv[2], "w");

    //char* input_file = argv[1];
    //char* output_file = argv[2];
    

	lexer(tokenTable, input_file, output_file);
    
    printf("postlexer\n");
    
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

