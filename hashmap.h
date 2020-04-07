#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

struct map_entry{
	char* key;
	char* value;
	struct map_entry* next;
};

struct hash_table{
	int size;   
	struct map_entry **table;
};

int createHash(struct hash_table* hashTable, char* key);

struct map_entry* createEntry(char* key, char* value);

void insertEntry(struct hash_table* hashTable, char* key, char* value);

struct hash_table* createHashTable(int size);

char* getValue(struct hash_table* hashTable, char* key);

