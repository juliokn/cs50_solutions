// Implements a dictionary's functionality
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"

//initiliazing the global variables

unsigned int word_counter = 0;
int hash_index = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //we hash the word so we know which bucket to search
    
    hash_index = hash(word);
   
    node* tmp = table[hash_index];
   
   //as long the node is not empty, we compare
    while (tmp != NULL)
    {
        //strcasecmp compare without paying attention to case
        if (strcasecmp(word, tmp->word) == 0)
        {
            //if it's equal, then it's right, and returns true
            return true;
        }
        //else the node turns into the next node so we check until the line ends
        tmp = tmp->next;
    }
    //if the list ends and we can't find the word, the word is misspelled, and it returns false
    return false;   
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //i adapted djb2, from dan bernstein, which can be found here: http://www.cse.yorku.ca/%7Eoz/hash.html
    unsigned long hash_value = 5381;
    int c;

    while ((c = toupper(*word++)))
    {
        hash_value = (((hash_value << 5) + hash_value) + c);
    }

    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //first we open the file and check for errors
    FILE *file_to_read = fopen(dictionary, "r");
    
    if (file_to_read == NULL)
    {
        return false;
    }
    
    char x [LENGTH + 1];
    
    //we read each list (line) of the provided dictionary to load each word
    while (fscanf(file_to_read, "%s", x) != EOF)
    {
        node* tmp = malloc(sizeof(node));
        
        if (tmp == NULL)
        {
            return false;
        }
        
        strcpy(tmp->word, x);
        
        //we hash using the hash function, and store
        
        hash_index = hash(tmp->word);
        
        tmp->next = table[hash_index];
        table[hash_index] = tmp;
        word_counter++;
    }
    
    //remember to close the file after we're done
    fclose(file_to_read);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //the variable is already initialized in the beginning, and used during load
    //so we'll just return it here
    if (word_counter > 0)
    {
        return word_counter;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //we go list by list, from 0 to N
    for (int i = 0; i < N; i++)
    {
        //we create a temp node to store the head of the list
        node* ptr = table[i];
        
        //as long this node isn't NULL, we'll go to the next and free it
        //so if we have a->b->c in this order, we'll destroy a, b and c
        while (ptr != NULL)
        {
            node* tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
        
        //when we reach the end of the loop and everything is freed, returns true
        if (i == N - 1 && ptr == NULL)
        {
            return true;
        }
    }
    //if everythings goes bad, returns false
    return false;
}

