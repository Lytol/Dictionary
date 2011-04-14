#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

#define DEBUG 1
#if DEBUG
    #include <stdio.h>
    #define TRACE(...) fprintf(stderr, __VA_ARGS__)
#else
    #define TRACE(...)
#endif


Dictionary *dictionary_create(int max_size) {
  Dictionary *new_dictionary = malloc(sizeof(Dictionary));
  int i;

  new_dictionary->entries = malloc(sizeof(DictionaryEntry *) * max_size);
  for(i = 0; i < max_size; i++) {
    new_dictionary->entries[i] = NULL;
  }
  new_dictionary->size = max_size;

  TRACE("Dictionary created - size: %d\n", new_dictionary->size);

  return new_dictionary;
}

void dictionary_insert(Dictionary *dict, char *key, int value) {
  int hashIndex;
  char *newKey;
  int keyLength = strlen(key);
  DictionaryEntry *newEntry, *current;
  
  newKey = (char *) malloc(keyLength + 1);
  strncpy(newKey, key, keyLength);
  newKey[keyLength] = '\0';

  newEntry = malloc(sizeof(DictionaryEntry));
  newEntry->key = newKey;
  newEntry->value = value;
  newEntry->next = NULL;

  hashIndex = _dictionary_hashing_function(key, dict->size);

  if(dict->entries[hashIndex] == NULL) {
    dict->entries[hashIndex] = newEntry;
  } else {
    current = dict->entries[hashIndex];
    while(current->next != NULL) {
      current = current->next;
    }
    current->next = newEntry;
  }

  TRACE("Inserted entry - k: %s v: %d\n", newEntry->key, newEntry->value);
}

int dictionary_search(Dictionary *dict, char *key) {
  int keyLength = strlen(key);
  int hashIndex = _dictionary_hashing_function(key, dict->size);
  DictionaryEntry *current = dict->entries[hashIndex];

  while(current != NULL) {
    if(strncmp(current->key, key, keyLength) == 0) {
      TRACE("Found entry - k: %s v: %d\n", current->key, current->value);
      return current->value;
    }
    current = current->next;
  }

  TRACE("Entry not found!\n");
  return DICTIONARY_NOT_FOUND;
}

void dictionary_delete(Dictionary *dict, char *key) {
  DictionaryEntry *previous, *current;
  int keyLength = strlen(key);
  int hashIndex = _dictionary_hashing_function(key, dict->size);

  previous = current = dict->entries[hashIndex];

  while(current != NULL) {
    if(strncmp(current->key, key, keyLength) == 0) {
      break;
    }
    previous = current;
    current = current->next;
  }

  if(current == NULL) {
    TRACE("Entry not found for deletion!\n");
  } else {
    if(current == previous) {
      dict->entries[hashIndex] = NULL;
    } else {
      previous->next = current->next;
    }
    TRACE("Deleted entry - k: %s v: %d\n", current->key, current->value);
    _dictionary_entry_free(current);
  }
}

void dictionary_free(Dictionary *dict) {
  int i;
  DictionaryEntry *next_entry, *current_entry;

  for(i = 0; i < dict->size; i++) {
    next_entry = current_entry = dict->entries[i];
    while(next_entry != NULL) {
      next_entry = current_entry->next;
      _dictionary_entry_free(current_entry);
      current_entry = next_entry;
    }
  }

  free(dict->entries);
  free(dict);

  TRACE("Dictionary free!\n");
}

/*
 * Helper functions
 *
 */

int _dictionary_hashing_function(char *key, int max_size) {
  int i, value = 0;
  int key_length = strlen(key);

  if(key_length <= 0) {
    return -1;
  }

  for(i = 0; i < key_length; i++) {
    value += (int) key[i];
  }

  return (value % max_size);
}

void _dictionary_entry_free(DictionaryEntry *entry) {
  TRACE("Freeing DictionaryEntry - k: %s v: %d\n", entry->key, entry->value);
  free(entry->key);
  free(entry);
}
