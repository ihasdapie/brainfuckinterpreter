/* A HashMap Implementation
 * Brian Chen | 2020
 * 
 * based off logic from https://gist.github.com/tonious/1377667
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

/*-----------------------------------------------------------------------------------------------*/

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
/*
int main(){

    struct hash_table* map = createHashTable(10000);
    insertEntry(map, "k1", "v1");  
    insertEntry(map, "k2", "v2");  
    insertEntry(map, "k3", "v3");  
    insertEntry(map, "k4", "v4");  
    insertEntry(map, "k5", "v5");  
	
    printf("key: %s, value: %s\n", "k1", getValue(map, "k1"));
    printf("key: %s, value: %s\n", "k2", getValue(map, "k2"));
    printf("key: %s, value: %s\n", "k3", getValue(map, "k3"));
    printf("key: %s, value: %s\n", "k4", getValue(map, "k4"));
    printf("key: %s, value: %s\n", "k5", getValue(map, "k5"));

    return 0;
}
*/	
