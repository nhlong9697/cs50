/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include "dictionary.h"
//define size for the hashtable
#define SIZE 1000000
//create node data structure for linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
//create hashtable
node* hashtable[SIZE];
//create variable for dictionary size
int dictSize = 0;
// Ref: https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
int hash(const char *word)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(word); i<n; i++) {
        hash = (hash << 2) ^ word[i];
    }
    return hash % SIZE;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    //open dictionary 
    FILE* file = fopen(dictionary,"r");
    if (file == NULL) 
    {
        return false;
    }
    //create an array to store the word
    char word[LENGTH+1];
    //scan and load word into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        //increase dictionary size
        dictSize++;
        //allocate memory for new word
        node* new_node = malloc(sizeof(node));
        //unload the dictionary if there is not enough memory
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        //copy word into node
        else
        {
            strcpy(new_node->word, word);
        }
        //hash the word
        int index = hash(word);
        //insert if the index is not empty
        if (hashtable[index] == NULL)
        {
            hashtable[index] = new_node;
            new_node->next= NULL;
            
        }
        //insert node if the index is empty
        else
        {
            new_node->next = hashtable[index];
            hashtable[index] = new_node;
        }
        
    }
    //close file
    fclose(file);
    //return true if succeed
    return true;
        
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // create char array to store copy of word
    // word is a const char* and non-read actions cannot be performed on it
    int len = strlen(word);
    char word_copy[len + 1];
    
    // convert word to lowercase and store it in word_copy
    for (int i = 0; i < len; i++)
    {
       word_copy[i] = tolower(word[i]);
    }
    
    // add null terminator to end of char array
    word_copy[len] = '\0';
    //indexing the word
    int index = hash(word_copy);
    //create cursor
    node* cursor = hashtable[index];
    //if the hashtable is empty or in other words there's no word that match the hashtable return false
    if (hashtable[index] ==  NULL)
    {
        return false;
    }
    //if the word match the hashtable check if the word exist in that hashtable
    while(cursor != NULL)
    {
        if (strcasecmp(word_copy, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    //return false if the word can't be found
    return false;
    
    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    if (dictSize > 0)
        return dictSize;
    else
        return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    // create a variable to go through index
    int index = 0;
    
    // iterate through entire hashtable array
    while (index < SIZE)
    {
        //create a cursor
        node *cursor = hashtable[index];
        //free the memory for each node that the cursor pass through
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        //increase index to move to another index of the hashtable
        index++;
    }
    
    // return true if successful
    return true;
}
