#ifndef DICTIONARY_H
#define DICTIONARY_H

#define DICTIONARY_NOT_FOUND -1
/*
 * Dictionary data types
 *
 */
typedef struct DictionaryEntry {
  char *key;
  int value;
  struct DictionaryEntry *next;
} DictionaryEntry;

typedef struct Dictionary {
  DictionaryEntry **entries;
  int size;
} Dictionary;


/*
 * Core functions
 *
 */

Dictionary *dictionary_create(int max_size);
void dictionary_insert(Dictionary *dict, char *key, int value);
int dictionary_search(Dictionary *dict, char *key);
void dictionary_delete(Dictionary *dict, char *key);
void dictionary_free(Dictionary *dict);

/*
 * Helper / private functions
 *
 */

int _dictionary_hashing_function(char *key, int max_size);
void _dictionary_entry_free(DictionaryEntry *entry);

#endif /* DICTIONARY_H */
