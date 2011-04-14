#include <stdio.h>
#include "dictionary.h"

#define HASH_SIZE 100

int main(int argc, char *argv[]) {
  Dictionary *dictionary;

  dictionary = dictionary_create(HASH_SIZE);
  dictionary_insert(dictionary, "brian", 0);
  dictionary_insert(dictionary, "will", 1);
  dictionary_insert(dictionary, "jarad", 2);
  dictionary_insert(dictionary, "adam", 3);
  dictionary_insert(dictionary, "neal", 4);

  dictionary_search(dictionary, "brian");
  dictionary_search(dictionary, "other");

  dictionary_delete(dictionary, "brian");

  dictionary_search(dictionary, "brian");
  dictionary_search(dictionary, "other");

  dictionary_free(dictionary);

  return 0;
}
